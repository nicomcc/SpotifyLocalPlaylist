#include "playlist.h"

Playlist::Playlist()
{

}

Playlist::Playlist(QString n)
{
    name = n;
    playlist.clear();
}

Playlist::Playlist(QList<Track> pl)
{
    playlist = pl;
}

void Playlist::setName(QString n)
{
    name = n;
}

void Playlist::Update(QList<Track> pl)
{
    playlist = pl;
}

void Playlist::AddTrack(Track t)
{
    playlist.append(t);
}

void Playlist::RemoveTrack(Track t)
{
    if(getSize() > 0)
    {
        for (int i=0; i < getSize(); i++)
            if (playlist[i].getName() == t.getName() && playlist[i].getArtist() == t.getArtist() && playlist[i].getAlbum() == t.getAlbum())
                playlist.removeAt(i);
    }
}

Track Playlist::getTrack(int index)
{
    return playlist[index];
}

bool Playlist::isTrackAlreadyOnList(Track t)
{

    for (int i=0; i < getSize(); i++)
        if (playlist[i].getName() == t.getName() && playlist[i].getArtist() == t.getArtist() && playlist[i].getAlbum() == t.getAlbum())
            return true;

    return false;
}
