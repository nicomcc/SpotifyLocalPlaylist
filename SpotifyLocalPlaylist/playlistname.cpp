#include "playlistname.h"
#include "ui_playlistname.h"

playlistName::playlistName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistName)
{
    ui->setupUi(this);
}

playlistName::~playlistName()
{
    delete ui;
}

void playlistName::on_buttonBox_accepted()
{

 for (int i = 0; i < playlistNames.count(); i++)
   {
       if (playlistNames[i] == ui->lineEdit->text())
       {
           QMessageBox::warning(this, "Error", "Playlist name is already being used", QMessageBox::Ok);
           return;
       }
       qDebug() << playlistNames[i] << endl;
   }

   name = ui->lineEdit->text();
   accept();
}

void playlistName::on_buttonBox_rejected()
{
    reject();
}

QString playlistName::getName()
{
    return name;
}

void playlistName::setPlaylistNames(QList<QString> l)
{
    for (int i = 0; i < l.count(); i++)
    {
        playlistNames.append(l[i]);
    }
}
