#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include "track.h"
#include <QDebug>

class Playlist : Track
{

private:
    QString name;
    QList <Track> playlist;

public:


    Playlist();
    Playlist(QList<Track> pl);

    void setName (QString n);

    void Update(QList<Track> pl);
    void AddTrack(Track t);
    void RemoveTrack(Track t);

    Track getTrack(int index);
    Track getLastTrack() {return playlist[getSize()-1];}
    int getSize(){return playlist.count();}


    bool isTrackAlreadyOnList(Track t);
};

#endif // PLAYLIST_H
