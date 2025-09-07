#pragma once

#include "SEScenntShotInter.h"

class SEWindowScenntShot : public SEScenntShotInter
{
	Q_OBJECT
public:
	SEWindowScenntShot(QObject* parent = nullptr);

public:
	// 通过 SEScenntShotInter 继承
	void startScreenshot() override;

private:
    // 截图遮罩窗口
    QWidget* m_overlayWidget;
    // 屏幕原始图像
    QPixmap m_screenPixmap;
    // 当前选中的区域
    QRect m_selectedArea;
    // 是否正在截图
    bool m_isCapturing;
};

