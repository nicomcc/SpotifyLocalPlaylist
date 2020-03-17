/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGrant;
    QAction *actionGet_Playlists;
    QAction *actionGet_User_Information;
    QAction *actionSearch_Music;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *teOutput;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineMusic;
    QPushButton *bt_search;
    QMenuBar *menuBar;
    QMenu *menuWeb_API;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(439, 349);
        actionGrant = new QAction(MainWindow);
        actionGrant->setObjectName(QString::fromUtf8("actionGrant"));
        actionGet_Playlists = new QAction(MainWindow);
        actionGet_Playlists->setObjectName(QString::fromUtf8("actionGet_Playlists"));
        actionGet_Playlists->setEnabled(false);
        actionGet_User_Information = new QAction(MainWindow);
        actionGet_User_Information->setObjectName(QString::fromUtf8("actionGet_User_Information"));
        actionGet_User_Information->setEnabled(false);
        actionSearch_Music = new QAction(MainWindow);
        actionSearch_Music->setObjectName(QString::fromUtf8("actionSearch_Music"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);

        teOutput = new QPlainTextEdit(centralWidget);
        teOutput->setObjectName(QString::fromUtf8("teOutput"));

        verticalLayout->addWidget(teOutput);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        verticalSpacer = new QSpacerItem(20, 141, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lineMusic = new QLineEdit(centralWidget);
        lineMusic->setObjectName(QString::fromUtf8("lineMusic"));

        verticalLayout->addWidget(lineMusic);

        bt_search = new QPushButton(centralWidget);
        bt_search->setObjectName(QString::fromUtf8("bt_search"));

        verticalLayout->addWidget(bt_search);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 439, 22));
        menuWeb_API = new QMenu(menuBar);
        menuWeb_API->setObjectName(QString::fromUtf8("menuWeb_API"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuWeb_API->menuAction());
        menuWeb_API->addAction(actionGrant);
        menuWeb_API->addAction(actionGet_Playlists);
        menuWeb_API->addAction(actionGet_User_Information);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionGrant->setText(QCoreApplication::translate("MainWindow", "Grant", nullptr));
        actionGet_Playlists->setText(QCoreApplication::translate("MainWindow", "Get Playlists", nullptr));
#if QT_CONFIG(tooltip)
        actionGet_Playlists->setToolTip(QCoreApplication::translate("MainWindow", "Query Playlists from Webapi", nullptr));
#endif // QT_CONFIG(tooltip)
        actionGet_User_Information->setText(QCoreApplication::translate("MainWindow", "Get User Information", nullptr));
        actionSearch_Music->setText(QCoreApplication::translate("MainWindow", "Search Music", nullptr));
        bt_search->setText(QCoreApplication::translate("MainWindow", "Search Music", nullptr));
        menuWeb_API->setTitle(QCoreApplication::translate("MainWindow", "Web API", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
