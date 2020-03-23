#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOAuth2AuthorizationCodeFlow>
#include "track.h"
#include <QList>
#include "playlist.h"
#include "playlistname.h"
#include <QFile>
#include <QMediaPlaylist>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btRemove_clicked();

    void on_btPlay_clicked();

    void on_btCreatePlaylist_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_btDeletePl_clicked();

    void on_btPause_clicked();

    void on_searchListWidget_currentRowChanged(int currentRow);

    void on_btStop_clicked();

    void on_btNext_clicked();

    void on_btPrevious_clicked();

    void on_positionChanged(int position);

    void on_durationChanged(int duration);

    void on_volumeSlider_sliderMoved(int position);

private:
    Ui::Widget *ui;

    QOAuth2AuthorizationCodeFlow spotify;

    void saveUser();
    void loadUser();
    void updatePlaylistWidget(Playlist p);
    void updateComboBox();

    QList <class::Track> searchList;

    QList <Playlist> user;

    QMediaPlayer *QMPlayer;
    QMediaPlaylist *QMplaylist;

    int *currentPlaylistId;
};
#endif // WIDGET_H
