/********************************************************************************
** Form generated from reading UI file 'blurfilterMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLURFILTERMAINWINDOW_H
#define UI_BLURFILTERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_blurfilterMainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *blurfilterMainWindow)
    {
        if (blurfilterMainWindow->objectName().isEmpty())
            blurfilterMainWindow->setObjectName(QStringLiteral("blurfilterMainWindow"));
        blurfilterMainWindow->resize(600, 250);
        actionExit = new QAction(blurfilterMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralwidget = new QWidget(blurfilterMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 100, 113, 32));
        blurfilterMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(blurfilterMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        blurfilterMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(blurfilterMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        blurfilterMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(blurfilterMainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), blurfilterMainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(blurfilterMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *blurfilterMainWindow)
    {
        blurfilterMainWindow->setWindowTitle(QApplication::translate("blurfilterMainWindow", "blurfilter", 0));
        actionExit->setText(QApplication::translate("blurfilterMainWindow", "Exit", 0));
        pushButton->setText(QApplication::translate("blurfilterMainWindow", "PushButton", 0));
        menuFile->setTitle(QApplication::translate("blurfilterMainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class blurfilterMainWindow: public Ui_blurfilterMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLURFILTERMAINWINDOW_H
