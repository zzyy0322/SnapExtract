#ifndef MYQTWINDOW_H
#define MYQTWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"  // 引用 uic 生成的头文件

class MyQtWindow : public QMainWindow {
    Q_OBJECT  // 必须添加，需要 moc 处理
public:
    MyQtWindow(QWidget* parent = nullptr);
private:
    Ui::MainWindow ui;  // 关联 UI
};
#endif