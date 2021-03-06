#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QUrl>
#include <QDate>

class Track
{
private:
    QString name;
    QString artist;
    QUrl link;
    QUrl preview;
    QString album;
    QDate release_date;

public:
    Track();
    Track(QString name);
    Track(QString name, QString artist, QString album = "", QUrl link = QUrl(), QUrl preview = QUrl());

    //get methods
    QString getName() {return name;}
    QString getArtist() {return artist;}
    QString getAlbum() {return album;}
    QUrl getLink() {return link;}
    QUrl getPreview() {return preview;}
    QDate getReleaseDate() {return release_date;}

    //set methods
    void setName(QString newName);
    void setArtist(QString newArtist);
    void setAlbum(QString newAlbum);
    void setLink(QUrl newLink);
    void setPreview(QUrl p);
    void setReleaseDate(QDate newDate);
};

#endif // TRACK_H
