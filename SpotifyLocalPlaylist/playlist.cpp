#include "playlist.h"

Playlist::Playlist()
{

}

Playlist::Playlist(QList<Track> pl)
{
    playlist = pl;
}

void Playlist::Update(QList<Track> pl)
{
    playlist = pl;
}

void Playlist::AddTrack(Track t)
{
    playlist.append(t);
}

Track Playlist::getTrack(int index)
{
    return playlist[index];
}

bool Playlist::isTrackAlreadyOnList(Track t)
{

    for (int i=0; i < getSize(); i++)
        if (playlist[i].getName() == t.getName())
            return true;

    return false;
}