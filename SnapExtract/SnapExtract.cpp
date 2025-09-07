#include "pch.h"
#include <QApplication>
#include "SEMainWindow.h"
#include "SEWindowScenntShot.h"

// 原有业务逻辑
void originalLogic() {
    // ... 你的现有代码 ...
}

int main(int argc, char* argv[]) {
    // 1. 初始化 Qt 应用（必须在所有 Qt 对象前创建）
    QApplication app(argc, argv);

    // 2. 执行原有业务逻辑
    originalLogic();

    SEWindowScenntShot pWindowShot;

    // 3. 显示 Qt 窗口
    SEMainWindow window;
    window.setScenntShotInterface(&pWindowShot);
    window.show();

    // 4. 启动 Qt 事件循环（程序会阻塞在此，直到窗口关闭）
    return app.exec();
}