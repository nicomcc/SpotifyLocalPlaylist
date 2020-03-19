#include "playlistname.h"
#include "ui_playlistname.h"

playlistName::playlistName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistName)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
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
   }

   if (isThereInvalidCharacters(ui->lineEdit->text()))
   {
       QMessageBox::warning(this, "Error", "Name contains invalid character", QMessageBox::Ok);
        return;
   }

   name = ui->lineEdit->text();
   accept();
}

void playlistName::on_buttonBox_rejected()
{
    reject();
}

bool playlistName::isThereInvalidCharacters(QString s)
{
    s =  ui->lineEdit->text();
    for (int i = 0; i < s.count(); i++)
    {
        QChar c = s[i];
        if (c.unicode() < 48  || c.unicode() > 122)
            return true;
        if (c.unicode() > 57 && c.unicode() < 65)
            return true;
        if (c.unicode() > 90 && c.unicode() < 97)
            return true;
    }
    return false;
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
