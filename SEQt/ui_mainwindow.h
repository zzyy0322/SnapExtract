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
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtSnap;
    QPushButton *BtReSnap;
    QComboBox *comBoxType;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtSetting;
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
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        BtSnap = new QPushButton(centralwidget);
        BtSnap->setObjectName("BtSnap");

        horizontalLayout->addWidget(BtSnap);

        BtReSnap = new QPushButton(centralwidget);
        BtReSnap->setObjectName("BtReSnap");

        horizontalLayout->addWidget(BtReSnap);

        comBoxType = new QComboBox(centralwidget);
        comBoxType->setObjectName("comBoxType");

        horizontalLayout->addWidget(comBoxType);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtSetting = new QPushButton(centralwidget);
        BtSetting->setObjectName("BtSetting");

        horizontalLayout->addWidget(BtSetting);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        framePicture = new QFrame(centralwidget);
        framePicture->setObjectName("framePicture");
        framePicture->setMinimumSize(QSize(0, 100));
        framePicture->setFrameShape(QFrame::Shape::StyledPanel);
        framePicture->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_2->addWidget(framePicture);

        frameShow = new QFrame(centralwidget);
        frameShow->setObjectName("frameShow");
        frameShow->setMinimumSize(QSize(0, 100));
        frameShow->setFrameShape(QFrame::Shape::StyledPanel);
        frameShow->setFrameShadow(QFrame::Shadow::Raised);

        horizontalLayout_2->addWidget(frameShow);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
