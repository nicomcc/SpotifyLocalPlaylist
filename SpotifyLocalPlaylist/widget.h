#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOAuth2AuthorizationCodeFlow>
#include "track.h"
#include <QList>


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

private:
    Ui::Widget *ui;

    QOAuth2AuthorizationCodeFlow spotify;

    QList <class::track> searchList;
};
#endif // WIDGET_H
