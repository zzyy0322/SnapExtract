#include "pch.h"
#include "MyQtWindow.h"

MyQtWindow::MyQtWindow(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);  // ��ʼ�� UI
    setWindowTitle("Qt ����ʾ��");
    // ������������źŲ�
}