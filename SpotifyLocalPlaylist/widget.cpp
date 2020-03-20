#include "widget.h"
#include "ui_widget.h"

#include <QtNetworkAuth>
#include <QDesktopServices>
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    loadUser();

    const QString clientId = "eaf37929f4c24661ab28bd1854576bce";
    const QString clientSecret = "d166eb2ab7c841cb941bc50a54f7832f";

    auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);

    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setClientIdentifier(clientId);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private");

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);

    spotify.grant();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btSearch_clicked()
{
    QString track = ui->lineMusic->text();
    if(track != "")
    {
    QUrl u ("https://api.spotify.com/v1/search?q=" + track + "&type=track");

    auto reply = spotify.get(u);


    connect (reply, &QNetworkReply::finished, [=]() {
           //if connection finds error
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString() << endl;
            return;
        }

   if(!reply->error()){
       const auto data = reply->readAll();

       searchList.clear();

       QJsonDocument doc = QJsonDocument::fromJson(data);

       if (doc.isNull())
       {
            qDebug()<< "Document is null: " << doc.isNull() << endl;
            return;
       }

       QJsonObject root = doc.object();  // root contains only one object, artist
       QJsonValue art = root.value("tracks"); // get artists object
       QJsonValue items = art.toObject().value("items"); //get items value and check if it is an array in artist object

       QString track, artist, album;
       QUrl link;

       if (items.isArray())
          {
           QJsonArray itemsArray = items.toArray(); //convert items to array

           for(int i = 0; i < itemsArray.count(); i++)
           {
               QJsonObject subItems = itemsArray.at(i).toObject();
               track = subItems.value("name").toString();
               link = subItems.value("external_urls").toObject().value("spotify").toString();
               album = subItems.value("album").toObject().value("name").toString();

               QJsonArray itemArtist = subItems.value("artists").toArray();
               for(int j = 0; j < itemArtist.count(); j++)
                   artist = itemArtist.at(j).toObject().value("name").toString();  //gets artist name from artist array

               class::Track searchedTrack(track, artist, album, link);
               searchList.append(searchedTrack);
           }

           ui->searchListWidget->clear();
           for (int i = 0; i < searchList.count(); i++)
           {
               ui->searchListWidget->addItem("Track: " + searchList[i].getName() + "        Artist: " + searchList[i].getArtist() +
                                       "        Album: " + searchList[i].getAlbum());
           }

          }
       }
    });
    }
}

void Widget::on_btAdd_clicked()
{
    //check if any row is selected
    if (ui->searchListWidget->currentIndex().row() != -1)
    {
        class::Track selectedTrack = searchList[ui->searchListWidget->currentIndex().row()];

        //if track isn't already on playlist
        if(!user[ui->comboBox->currentIndex()].isTrackAlreadyOnList(selectedTrack))
        {
            user[ui->comboBox->currentIndex()].AddTrack(selectedTrack);

            ui->playlistListWidget->addItem("Track: " + user[ui->comboBox->currentIndex()].getLastTrack().getName() + "        Artist: " + user[ui->comboBox->currentIndex()].getLastTrack().getArtist() +
                                            "        Album: " + user[ui->comboBox->currentIndex()].getLastTrack().getAlbum());
            saveUser();
        }

        else
           QMessageBox::warning(this, "Message", "Track is already on playlist", QMessageBox::Ok);
    }
}


void Widget::on_btRemove_clicked()
{
    if (ui->comboBox->count() > 0)
    {
        if (user[ui->comboBox->currentIndex()].getSize() > 0)
        {
            //check if row is selected
            if (ui->playlistListWidget->currentIndex().row() != -1)
            {
                Track selectedTrack = user[ui->comboBox->currentIndex()].getTrack(ui->playlistListWidget->currentIndex().row());
                user[ui->comboBox->currentIndex()].RemoveTrack(selectedTrack);
                ui->playlistListWidget->takeItem(ui->playlistListWidget->currentIndex().row());
                saveUser();
            }
        }
    }
}


void Widget::on_btPlay_clicked()
{
   /*if (ui->searchListWidget->currentIndex().row() != -1 && playlist.getSize() > 0)
   {

    class::Track selectedTrack = playlist.getTrack(ui->playlistListWidget->currentIndex().row());

    QUrl u = selectedTrack.getLink();

    auto reply = spotify.put(u);




    connect (reply, &QNetworkReply::finished, [=]() {
           //if connection finds error
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString() << endl;
            return;
        }

        if(!reply->error()){

        }

        });
   }*/
}

void Widget::on_btCreatePlaylist_clicked()
{
    playlistName *dlg = new playlistName(this);

    QList <QString> names;
    for (int i=0; i < ui->comboBox->count(); i++)
        names.append(ui->comboBox->itemText(i));

    dlg->setPlaylistNames(names);

    dlg->exec();


    if (dlg->getName() != "")
    {
        Playlist a(dlg->getName());
        user.append(a);

        if(ui->comboBox->count() == 1 && user.count() == 1)
            ui->comboBox->setItemText(0, dlg->getName());

        else
            ui->comboBox->addItem(dlg->getName());

        //change index to last added
        ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);

        saveUser();
    }
}

void Widget::saveUser()
{
    QJsonDocument doc;

    QJsonArray arPList;

    for (int i = 0; i < user.count(); i++)
    {
        QJsonArray arTracks;
        for (int j = 0; j < user[i].getSize(); j++)
        {

        QJsonObject pTrack;
        pTrack.insert("name", user[i].getTrack(j).getName());
        pTrack.insert("album", user[i].getTrack(j).getAlbum());
        pTrack.insert("artist", user[i].getTrack(j).getArtist());
        arTracks.push_back(pTrack);
        }

        QJsonObject pList;
        pList.insert("name", user[i].getName());
        pList.insert("tracks", arTracks);

        arPList.push_back(pList);
    }

    QJsonObject defaultUser;
    defaultUser.insert("playlists", arPList);
    defaultUser.insert("name", "localUser");

    doc.setObject(defaultUser);

    qDebug() << doc << endl;

    QString filename = "localUser.json";
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        qDebug() << "failed to open file" << endl;
        return;
    }
    file.write(doc.toJson());
    file.close();
}

void Widget::loadUser()
{
    QString filename = "localUser.json";
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "failed to open file" << endl;
        return;
    }

    QJsonParseError JsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    qDebug() << doc << endl;

    QJsonObject root = doc.object();  // root contains only one object, artist
    QJsonArray playlistsArray = root.value("playlists").toArray(); // get artists object

    for(int i = 0; i < playlistsArray.count(); i++)
    {
        QString playlistName = playlistsArray[i].toObject().value("name").toString();
        Playlist p(playlistName);
        user.append(p);
        QJsonArray tracks = playlistsArray[i].toObject().value("tracks").toArray();
        for (int j = 0; j < tracks.count(); j++)
        {
            QString trackName, trackAlbum, trackArtist;
            trackName = tracks[j].toObject().value("name").toString();
            trackAlbum = tracks[j].toObject().value("album").toString();
            trackArtist = tracks[j].toObject().value("artist").toString();
            Track t (trackName, trackArtist, trackAlbum);
            user[i].AddTrack(t);
        }
    }

    updateComboBox();
}

void Widget::updatePlaylistWidget(Playlist p)
{
    ui->playlistListWidget->clear();
   if (ui->comboBox->count() > 0)
   {
       for (int i=0; i < p.getSize(); i++)
       {
           ui->playlistListWidget->addItem("Track: " + p.getTrack(i).getName() + "        Artist: " + p.getTrack(i).getArtist() +
                                          "        Album: " + p.getTrack(i).getAlbum());
       }
   }
}

void Widget::updateComboBox()
{
    if (user.count() > 0)
    {
        for (int i = 0; i < user.count(); i++)
        {
            if (i == 0)
                ui->comboBox->setItemText(0, user[i].getName());
            else
                ui->comboBox->addItem(user[i].getName());
        }

        updatePlaylistWidget(user[0]);
    }

}

void Widget::on_btSave_clicked()
{
  /*  for (int i = 0; i < user.count(); i++)
    {
        for (int j = 0; j < user[i].getSize(); j++)
        {
        qDebug() << "playlist " << i <<"track: " << j << user[i].getTrack(j).getName() << user[i].getTrack(j).getAlbum() << user[i].getTrack(j).getArtist();
        }
    }*/

    saveUser();
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->label->setText("Playlist: " + ui->comboBox->currentText());
     /*ui->playlistListWidget->clear();
    if (ui->comboBox->count() > 0)
    {
        for (int i=0; i < user[ui->comboBox->currentIndex()].getSize(); i++)
        {
            ui->playlistListWidget->addItem("Track: " + user[ui->comboBox->currentIndex()].getTrack(i).getName() + "        Artist: " + user[ui->comboBox->currentIndex()].getTrack(i).getArtist() +
                                           "        Album: " + user[ui->comboBox->currentIndex()].getTrack(i).getAlbum());
        }
    }*/
    updatePlaylistWidget(user[ui->comboBox->currentIndex()]);
}

void Widget::on_btDeletePl_clicked()
{
    if(user.count() > 0)
    {
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::question(this, "Message", "Are you sure you want to delete <" + ui->comboBox->currentText() + "> playlist?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (confirm == QMessageBox::Yes)
        {
            if(ui->comboBox->count() > 1)
            {
                user.removeAt(ui->comboBox->currentIndex());
                ui->comboBox->removeItem(ui->comboBox->currentIndex());
                updatePlaylistWidget(user[ui->comboBox->currentIndex()]);
                saveUser();
            }
            else if (ui->comboBox->count() == 1 && user.count() > 0)
            {
                user.removeAt(ui->comboBox->currentIndex());
                ui->comboBox->setItemText(0, "<no playlists>");
                ui->playlistListWidget->clear();
                saveUser();
            }

        }
    }
    else if (ui->comboBox->count() == 1 && user.count() == 0)
    {
        QMessageBox::warning(this, "Message", "User has no playlist!", QMessageBox::Ok);
    }
}
