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

    //initialize button icons
    ui->btPlay->setIcon(QIcon(":/icons/play.png"));
    ui->btPause->setIcon(QIcon(":/icons/pause.png"));
    ui->btStop->setIcon(QIcon(":/icons/stop.png"));
    ui->btPrevious->setIcon(QIcon(":/icons/previous.png"));
    ui->btNext->setIcon(QIcon(":/icons/next.png"));

    //load playlists from json file
    loadUser();

    if(user.count() > 0)
        ui->label->setText("Playlist: " + ui->comboBox->currentText());

    const QString clientId = "eaf37929f4c24661ab28bd1854576bce";
    const QString clientSecret = "d166eb2ab7c841cb941bc50a54f7832f";

    auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);

    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setClientIdentifier(clientId);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private user-modify-playback-state");

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);

    spotify.grant();

    QMPlayer = new QMediaPlayer();
    QMplaylist = new QMediaPlaylist();
    currentPlaylistId = new int(0);


    connect(QMPlayer, &QMediaPlayer::positionChanged, this, &Widget::on_positionChanged);
    connect(QMPlayer, &QMediaPlayer::durationChanged, this, &Widget::on_durationChanged);

    qDebug() << "Path: " << QDir::currentPath() << endl;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btSearch_clicked()
{
    searchMusic();
}

void Widget::on_btAdd_clicked()
{
    addItemtoPlaylist();
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
                //stop player to prevent playlist trying to access out of boundaries index
                QMPlayer->stop();
            }
        }
    }
}


void Widget::on_btPlay_clicked()
{
    playTrack();
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
            pTrack.insert("preview_link", user[i].getTrack(j).getPreview().toString());
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

   // qDebug() << doc << endl;

    QString outputDir = QDir::currentPath(); // with "/" separators
    QString filename = "localUser.json";
    QString fileOut = outputDir+ "/" + filename;

    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        QMessageBox::warning(this, "Message", "Failed to save file!", QMessageBox::Ok);
        return;
    }
    file.write(doc.toJson());
    file.close();
}

void Widget::loadUser()
{
    QString outputDir = QDir::currentPath(); // with "/" separators
    QString filename = "localUser.json";
    QString fileOut = outputDir+ "/" + filename;

    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Couldn't find file!" << endl;
        return;
    }

    QJsonParseError JsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    //qDebug() << doc << endl;

    QJsonObject root = doc.object();  // root contains only one object, artist
    QJsonArray playlistsArray = root.value("playlists").toArray(); // get artists object

    for(int i = 0; i < playlistsArray.count(); i++)
    {
        QString playlistName = playlistsArray[i].toObject().value("name").toString();
        QUrl link, preview;

        Playlist p(playlistName);
        user.append(p);
        QJsonArray tracks = playlistsArray[i].toObject().value("tracks").toArray();
        for (int j = 0; j < tracks.count(); j++)
        {
            QString trackName, trackAlbum, trackArtist;
            trackName = tracks[j].toObject().value("name").toString();
            trackAlbum = tracks[j].toObject().value("album").toString();
            trackArtist = tracks[j].toObject().value("artist").toString();
            link = tracks[j].toObject().value("link").toString();
            preview = tracks[j].toObject().value("preview_link").toString();
            Track t (trackName, trackArtist, trackAlbum, link, preview);
            user[i].AddTrack(t);
        }
    }

    updateComboBox();
}

void Widget::updatePlaylistWidget(Playlist p)
{
    ui->playlistListWidget->clear();
   if (user.count() > 0)
   {
       for (int i=0; i < p.getSize(); i++)
       {
           QListWidgetItem* pItem = new QListWidgetItem("Track: " + p.getTrack(i).getName() + "        Artist: " + p.getTrack(i).getArtist() +
                                              "        Album: " + p.getTrack(i).getAlbum());
           ui->playlistListWidget->addItem(pItem);
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

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->label->setText("Playlist: " + ui->comboBox->currentText());

    if (QMPlayer->state()== QMediaPlayer::PausedState)
         QMPlayer->stop();

    updatePlaylistWidget(user[ui->comboBox->currentIndex()]);

    //select playing track if it matchs with playlist
    if(ui->comboBox->currentIndex() == *currentPlaylistId)
         ui->playlistListWidget->setCurrentRow(QMplaylist->currentIndex());
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

void Widget::on_btPause_clicked()
{
    QMPlayer->pause();
}

void Widget::on_searchListWidget_currentRowChanged(int currentRow)
{
    if (ui->searchListWidget->currentIndex().row() != -1)
    {
        if (searchList[currentRow].getPreview().toString() == "")
               ui->labelPreview->setText("Preview: Not Available");
        else
               ui->labelPreview->setText("Preview: Available         ");
    }
}

void Widget::on_btStop_clicked()
{
    QMPlayer->stop();
    ui->labelPlaying->setText("Playing: ");
}

void Widget::on_btNext_clicked()
{
        QMplaylist->next();
}

void Widget::on_btPrevious_clicked()
{
   //if(QMplaylist->currentIndex() > 0)
         QMplaylist->previous();
}

void Widget::on_positionChanged(int position)
{
    ui->progressSlider->setValue(position);
}

void Widget::on_durationChanged(int duration)
{
    ui->progressSlider->setMaximum(duration);
}

void Widget::on_volumeSlider_sliderMoved(int position)
{
    QMPlayer->setVolume(position);
}

void Widget::addItemtoPlaylist()
{
    //check if any row is selected
    if (ui->searchListWidget->currentIndex().row() != -1)
    {
    class::Track selectedTrack = searchList[ui->searchListWidget->currentIndex().row()];

    //check if track has preview available
    if (selectedTrack.getPreview().toString() != "")
    {
            //check if track isn't already on playlist
            if(!user[ui->comboBox->currentIndex()].isTrackAlreadyOnList(selectedTrack))
            {
                user[ui->comboBox->currentIndex()].AddTrack(selectedTrack);

                QListWidgetItem* pItem = new QListWidgetItem("Track: " + user[ui->comboBox->currentIndex()].getLastTrack().getName() + "        Artist: " + user[ui->comboBox->currentIndex()].getLastTrack().getArtist() +
                                                   "        Album: " + user[ui->comboBox->currentIndex()].getLastTrack().getAlbum());
                if(user[ui->comboBox->currentIndex()].getLastTrack().getPreview().toString() == "")
                   pItem->setForeground(Qt::red);
                ui->playlistListWidget->addItem(pItem);
                saveUser();
            }

            else
               QMessageBox::warning(this, "Message", "Track is already on playlist", QMessageBox::Ok);
        }
    else
         QMessageBox::warning(this, "Message", "This track has no preview available!", QMessageBox::Ok);
    }
}

void Widget::playTrack()
{
    if(user.size() > 0)
    {
        if(user[ui->comboBox->currentIndex()].getSize() > 0)
        {
            if(QMPlayer->state()!= QMediaPlayer::PausedState)
            {
               // currentPlaylistId = new int(ui->comboBox->currentIndex());
                *currentPlaylistId = ui->comboBox->currentIndex();
                QMplaylist = new QMediaPlaylist();

                //if no track is selected, start from beginning
                if(ui->playlistListWidget->currentRow() == -1)
                       ui->playlistListWidget->setCurrentRow(0);

              //start playlist from selected track
                for(int i = 0; i < user[ui->comboBox->currentIndex()].getSize();++i)
                      QMplaylist->addMedia(user[ui->comboBox->currentIndex()].getTrack(i).getPreview());


                QMPlayer->setPlaylist(QMplaylist);
                QMplaylist->setCurrentIndex(ui->playlistListWidget->currentRow());
            }
            QMPlayer->play();

            if (QMplaylist->currentIndex() >= 0)
             ui->labelPlaying->setText("Playing: " + user[*currentPlaylistId].getTrack(QMplaylist->currentIndex()).getName());

           connect (QMplaylist, &QMediaPlaylist::currentIndexChanged, [=]() {
                if(ui->comboBox->currentIndex() == *currentPlaylistId)
                     ui->playlistListWidget->setCurrentRow(QMplaylist->currentIndex());

                if (QMplaylist->currentIndex() >= 0)
                     ui->labelPlaying->setText("Playing: " + user[*currentPlaylistId].getTrack(QMplaylist->currentIndex()).getName());
            });
          }

        else
            QMessageBox::warning(this, "Message", "Playlist is empty!", QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this, "Message", "User has no playlists!", QMessageBox::Ok);
}

void Widget::searchMusic()
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
           QUrl link, preview;


           if (items.isArray())
              {
               QJsonArray itemsArray = items.toArray(); //convert items to array
               for(int i = 0; i < itemsArray.count(); i++)
               {
                   QJsonObject subItems = itemsArray.at(i).toObject();
                   track = subItems.value("name").toString();
                   preview = subItems.value("preview_url").toString();
                   link = subItems.value("external_urls").toObject().value("spotify").toString();
                   album = subItems.value("album").toObject().value("name").toString();

                   QJsonArray itemArtist = subItems.value("artists").toArray();
                   for(int j = 0; j < itemArtist.count(); j++)
                       artist = itemArtist.at(j).toObject().value("name").toString();  //gets artist name from artist array

                   class::Track searchedTrack(track, artist, album, link, preview);
                   searchList.append(searchedTrack);
               }

               ui->searchListWidget->clear();
               for (int i = 0; i < searchList.count(); i++)
               {
                   QListWidgetItem* pItem =new QListWidgetItem("Track: " + searchList[i].getName() + "        Artist: " + searchList[i].getArtist() +
                                                      "        Album: " + searchList[i].getAlbum());
                  if(searchList[i].getPreview().toString() == "")
                      pItem->setForeground(Qt::red);

                   ui->searchListWidget->addItem(pItem);
               }

              }
           }
        });
    }
}

void Widget::on_searchListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    addItemtoPlaylist();
}

void Widget::on_playlistListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    playTrack();
}

void Widget::on_lineMusic_returnPressed()
{
    searchMusic();
}
