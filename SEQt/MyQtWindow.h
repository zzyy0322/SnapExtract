#ifndef MYQTWINDOW_H
#define MYQTWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"  // ���� uic ���ɵ�ͷ�ļ�

class MyQtWindow : public QMainWindow {
    Q_OBJECT  // ������ӣ���Ҫ moc ����
public:
    MyQtWindow(QWidget* parent = nullptr);
private:
    Ui::MainWindow ui;  // ���� UI
};
#endif