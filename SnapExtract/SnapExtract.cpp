#include "pch.h"
#include <QApplication>
#include "SEMainWindow.h"
#include "SEWindowScenntShot.h"

// ԭ��ҵ���߼�
void originalLogic() {
    // ... ������д��� ...
}

int main(int argc, char* argv[]) {
    // 1. ��ʼ�� Qt Ӧ�ã����������� Qt ����ǰ������
    QApplication app(argc, argv);

    // 2. ִ��ԭ��ҵ���߼�
    originalLogic();

    SEWindowScenntShot pWindowShot;

    // 3. ��ʾ Qt ����
    SEMainWindow window;
    window.setScenntShotInterface(&pWindowShot);
    window.show();

    // 4. ���� Qt �¼�ѭ��������������ڴˣ�ֱ�����ڹرգ�
    return app.exec();
}