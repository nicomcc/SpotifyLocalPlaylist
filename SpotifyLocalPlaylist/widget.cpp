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

void Widget::on_btAdd_clicked()
{
    //check if any row is selected
    if (ui->searchListWidget->currentIndex().row() != -1)
    {
        class::Track selectedTrack = searchList[ui->searchListWidget->currentIndex().row()];

        //if track isn't already on playlist
        if(!playlist.isTrackAlreadyOnList(selectedTrack))
        {
            playlist.AddTrack(selectedTrack);

            ui->playlistListWidget->addItem("Track: " + playlist.getLastTrack().getName() + "        Artist: " + playlist.getLastTrack().getArtist() +
                                            "        Album: " + playlist.getLastTrack().getAlbum());
        }

        else
           QMessageBox::warning(this, "Message", "Track is already on playlist", QMessageBox::Ok);
    }
}


void Widget::on_btRemove_clicked()
{
    if (playlist.getSize() > 0)
    {
        //check if row is selected
        if (ui->playlistListWidget->currentIndex().row() != -1)
        {
            Track selectedTrack = playlist.getTrack(ui->playlistListWidget->currentIndex().row());
            playlist.RemoveTrack(selectedTrack);
            ui->playlistListWidget->takeItem(ui->playlistListWidget->currentIndex().row());
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
         ui->comboBox->addItem(dlg->getName());
}
