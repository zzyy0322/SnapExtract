#include "pch.h"
#include "SEWindowScenntShot.h"

SEWindowScenntShot::SEWindowScenntShot(QObject* parent):
	SEScenntShotInter(parent)
{
}

void SEWindowScenntShot::startScreenshot()
{
    //// ��ȡ��Ļ��ͼ
    //m_screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);

    //// ��ʾȫ������
    //m_overlayWidget->setGeometry(QGuiApplication::primaryScreen()->geometry());
    //m_overlayWidget->showFullScreen();

    m_isCapturing = true;
}
