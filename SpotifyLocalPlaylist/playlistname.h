#ifndef PLAYLISTNAME_H
#define PLAYLISTNAME_H

#include <QDialog>
#include "widget.h"
#include <QMessageBox>

namespace Ui {
class playlistName;
}

class playlistName : public QDialog
{
    Q_OBJECT

public:
    explicit playlistName(QWidget *parent = nullptr);
    ~playlistName();

     QString getName();
     void setPlaylistNames(QList<QString> l);


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:

    Ui::playlistName *ui;

    QList<QString> playlistNames;
    QString name;

    bool isThereInvalidCharacters(QString s);
};

#endif // PLAYLISTNAME_H
