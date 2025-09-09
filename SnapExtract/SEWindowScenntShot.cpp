#include "pch.h"
#include "SEWindowScenntShot.h"

SEWindowScenntShot::SEWindowScenntShot(QObject* parent):
	SEScenntShotInter(parent)
{
}

void SEWindowScenntShot::startScreenshot()
{
    /*��ǰ��Ļ��ͼ*/
    QPixmap screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);

    /*��������ʾ���ִ���*/
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
