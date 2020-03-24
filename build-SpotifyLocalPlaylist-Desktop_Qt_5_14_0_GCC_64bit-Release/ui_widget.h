/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btCreatePlaylist;
    QPushButton *btDeletePl;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *playlistListWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btRemove;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineMusic;
    QPushButton *btSearch;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelPreview;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *searchListWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btAdd;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelPlaying;
    QSpacerItem *horizontalSpacer_7;
    QSlider *progressSlider;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *btPrevious;
    QPushButton *btPause;
    QPushButton *btPlay;
    QPushButton *btStop;
    QPushButton *btNext;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSlider *volumeSlider;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(615, 519);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(86, 0));
        comboBox->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer_4 = new QSpacerItem(60, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btCreatePlaylist = new QPushButton(Widget);
        btCreatePlaylist->setObjectName(QString::fromUtf8("btCreatePlaylist"));

        horizontalLayout->addWidget(btCreatePlaylist);

        btDeletePl = new QPushButton(Widget);
        btDeletePl->setObjectName(QString::fromUtf8("btDeletePl"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btDeletePl->sizePolicy().hasHeightForWidth());
        btDeletePl->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btDeletePl);


        verticalLayout_2->addLayout(horizontalLayout);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        playlistListWidget = new QListWidget(Widget);
        playlistListWidget->setObjectName(QString::fromUtf8("playlistListWidget"));

        horizontalLayout_2->addWidget(playlistListWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btRemove = new QPushButton(Widget);
        btRemove->setObjectName(QString::fromUtf8("btRemove"));

        verticalLayout->addWidget(btRemove);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineMusic = new QLineEdit(Widget);
        lineMusic->setObjectName(QString::fromUtf8("lineMusic"));

        horizontalLayout_3->addWidget(lineMusic);

        btSearch = new QPushButton(Widget);
        btSearch->setObjectName(QString::fromUtf8("btSearch"));

        horizontalLayout_3->addWidget(btSearch);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        labelPreview = new QLabel(Widget);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));

        horizontalLayout_3->addWidget(labelPreview);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        searchListWidget = new QListWidget(Widget);
        searchListWidget->setObjectName(QString::fromUtf8("searchListWidget"));

        horizontalLayout_4->addWidget(searchListWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btAdd = new QPushButton(Widget);
        btAdd->setObjectName(QString::fromUtf8("btAdd"));

        verticalLayout_3->addWidget(btAdd);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        line_2 = new QFrame(Widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        labelPlaying = new QLabel(Widget);
        labelPlaying->setObjectName(QString::fromUtf8("labelPlaying"));

        horizontalLayout_6->addWidget(labelPlaying);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_6);

        progressSlider = new QSlider(Widget);
        progressSlider->setObjectName(QString::fromUtf8("progressSlider"));
        progressSlider->setMaximum(108);
        progressSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(progressSlider);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btPrevious = new QPushButton(Widget);
        btPrevious->setObjectName(QString::fromUtf8("btPrevious"));
        btPrevious->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btPrevious);

        btPause = new QPushButton(Widget);
        btPause->setObjectName(QString::fromUtf8("btPause"));
        btPause->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btPause);

        btPlay = new QPushButton(Widget);
        btPlay->setObjectName(QString::fromUtf8("btPlay"));
        btPlay->setStyleSheet(QString::fromUtf8(""));
        btPlay->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btPlay);

        btStop = new QPushButton(Widget);
        btStop->setObjectName(QString::fromUtf8("btStop"));
        btStop->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btStop);

        btNext = new QPushButton(Widget);
        btNext->setObjectName(QString::fromUtf8("btNext"));
        btNext->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btNext);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        volumeSlider = new QSlider(Widget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMinimum(0);
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(50);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(volumeSlider);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "<no playlists>", nullptr));

        btCreatePlaylist->setText(QCoreApplication::translate("Widget", "Create Playlist", nullptr));
        btDeletePl->setText(QCoreApplication::translate("Widget", "Delete Playlist", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Playlist", nullptr));
        btRemove->setText(QCoreApplication::translate("Widget", "Remove Track", nullptr));
        btSearch->setText(QCoreApplication::translate("Widget", "Search Track", nullptr));
        labelPreview->setText(QString());
        btAdd->setText(QCoreApplication::translate("Widget", "Add to Playlist", nullptr));
        labelPlaying->setText(QCoreApplication::translate("Widget", "Playing: ", nullptr));
        btPrevious->setText(QString());
        btPause->setText(QString());
        btPlay->setText(QString());
        btStop->setText(QString());
        btNext->setText(QString());
        label_2->setText(QCoreApplication::translate("Widget", "Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
