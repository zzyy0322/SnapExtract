#include "pch.h"
#include "MyQtWindow.h"

MyQtWindow::MyQtWindow(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);  // 初始化 UI
    setWindowTitle("Qt 整合示例");
    // 可以在这里绑定信号槽
}