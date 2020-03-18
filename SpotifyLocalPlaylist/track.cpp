#include "track.h"

track::track()
{

}

track::track(QString name, QString artist, QString album, QUrl link)
{
   this->name = name;
   this->artist = artist;
   this->album = album;
   this->link = link;
}

void track::setName(QString newName)
{
   name = newName;
}

void track::setArtist(QString newArtist)
{
    artist = newArtist;
}

void track::setAlbum(QString newAlbum)
{
    album = newAlbum;
}

void track::setLink(QUrl newLink)
{
    link = newLink;
}

void track::setReleaseDate(QDate newDate)
{
    release_date = newDate;
}

