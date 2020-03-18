#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOAuth2AuthorizationCodeFlow>
#include "track.h"
#include <QList>
#include "playlist.h"



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

private:
    Ui::Widget *ui;

    QOAuth2AuthorizationCodeFlow spotify;

    QList <class::Track> searchList;
    //QList <class::track> playlistList;

    Playlist playlist;
};
#endif // WIDGET_H
