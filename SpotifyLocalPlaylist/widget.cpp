#include "widget.h"
#include "ui_widget.h"

#include <QtNetworkAuth>
#include <QDesktopServices>


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

               class::track searchedTrack(track, artist, album, link);
               searchList.append(searchedTrack);
           }

           qDebug () << "List size: " << searchList.count() << endl;
           ui->searchList->clear();
           for (int i = 0; i < searchList.count(); i++)
           {
               ui->searchList->addItem("Track: " + searchList[i].getName() + " Artist: " + searchList[i].getArtist() +
                                       " Album: " + searchList[i].getAlbum());
           }

          }
       }
    });
}
