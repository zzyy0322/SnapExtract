#include "pch.h"
#include <QApplication>
#include "MyQtWindow.h"

// ԭ��ҵ���߼�
void originalLogic() {
    // ... ������д��� ...
}

int main(int argc, char* argv[]) {
    // 1. ��ʼ�� Qt Ӧ�ã����������� Qt ����ǰ������
    QApplication app(argc, argv);

    // 2. ִ��ԭ��ҵ���߼�
    originalLogic();

    // 3. ��ʾ Qt ����
    MyQtWindow window;
    window.show();

    // 4. ���� Qt �¼�ѭ��������������ڴˣ�ֱ�����ڹرգ�
    return app.exec();
}