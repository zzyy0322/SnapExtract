#include "pch.h"
#include "SEWindowScenntShot.h"

SEWindowScenntShot::SEWindowScenntShot(QObject* parent):
	SEScenntShotInter(parent)
{
}

void SEWindowScenntShot::startScreenshot()
{
    /*当前屏幕截图*/
    QPixmap screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);

    /*创建并显示遮罩窗口*/
    m_overlayWidget = new SEOverlayWidget(m_screenPixmap);
    m_overlayWidget->setGeometry(QGuiApplication::primaryScreen()->geometry());
    m_overlayWidget->showFullScreen();

    if (m_overlayWidget)
    {
        connect(m_overlayWidget, &SEOverlayWidget::selectionFinished,
            this, &SEWindowScenntShot::onScreenshotSelected);
    }

    m_isCapturing = true;
}

void SEWindowScenntShot::onScreenshotSelected(const QRect& rect)
{

}
