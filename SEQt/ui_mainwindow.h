/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtSnap;
    QPushButton *BtReSnap;
    QComboBox *comBoxType;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtSetting;
    QPushButton *BtMini;
    QPushButton *BtClose;
    QHBoxLayout *horizontalLayout_2;
    QFrame *framePicture;
    QFrame *frameShow;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 30, 591, 421));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        BtSnap = new QPushButton(widget);
        BtSnap->setObjectName("BtSnap");

        horizontalLayout->addWidget(BtSnap);

        BtReSnap = new QPushButton(widget);
        BtReSnap->setObjectName("BtReSnap");

        horizontalLayout->addWidget(BtReSnap);

        comBoxType = new QComboBox(widget);
        comBoxType->setObjectName("comBoxType");

        horizontalLayout->addWidget(comBoxType);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtSetting = new QPushButton(widget);
        BtSetting->setObjectName("BtSetting");

        horizontalLayout->addWidget(BtSetting);

        BtMini = new QPushButton(widget);
        BtMini->setObjectName("BtMini");

        horizontalLayout->addWidget(BtMini);

        BtClose = new QPushButton(widget);
        BtClose->setObjectName("BtClose");

        horizontalLayout->addWidget(BtClose);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        framePicture = new QFrame(widget);
        framePicture->setObjectName("framePicture");
        framePicture->setFrameShape(QFrame::Shape::StyledPanel);
        framePicture->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_2->addWidget(framePicture);

        frameShow = new QFrame(widget);
        frameShow->setObjectName("frameShow");
        frameShow->setFrameShape(QFrame::Shape::StyledPanel);
        frameShow->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_2->addWidget(frameShow);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        BtSnap->setText(QCoreApplication::translate("MainWindow", "\346\210\252\345\233\276", nullptr));
        BtReSnap->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\346\210\252\345\233\276", nullptr));
        BtSetting->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        BtMini->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\214\226", nullptr));
        BtClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
