#include "pch.h"
#include "SEWindowScenntShot.h"

SEWindowScenntShot::SEWindowScenntShot(QObject* parent):
	SEScenntShotInter(parent)
{
}

void SEWindowScenntShot::startScreenshot()
{
    //// »ñÈ¡ÆÁÄ»½ØÍ¼
    //m_screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);

    //// ÏÔÊ¾È«ÆÁÕÚÕÖ
    //m_overlayWidget->setGeometry(QGuiApplication::primaryScreen()->geometry());
    //m_overlayWidget->showFullScreen();

    m_isCapturing = true;
}
