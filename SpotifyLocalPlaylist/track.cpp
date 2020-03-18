#include "track.h"

Track::Track()
{

}

Track::Track(QString name, QString artist, QString album, QUrl link)
{
   this->name = name;
   this->artist = artist;
   this->album = album;
   this->link = link;
}

void Track::setName(QString newName)
{
   name = newName;
}

void Track::setArtist(QString newArtist)
{
    artist = newArtist;
}

void Track::setAlbum(QString newAlbum)
{
    album = newAlbum;
}

void Track::setLink(QUrl newLink)
{
    link = newLink;
}

void Track::setReleaseDate(QDate newDate)
{
    release_date = newDate;
}

