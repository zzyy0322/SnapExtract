#pragma once

#include "SEScenntShotInter.h"
#include "SEOverlayWidget.h"

class SEWindowScenntShot : public SEScenntShotInter
{
	Q_OBJECT
public:
	SEWindowScenntShot(QObject* parent = nullptr);
    virtual ~SEWindowScenntShot();

public:
	// 通过 SEScenntShotInter 继承
	void startScreenshot() override;

private slots:
    void onScreenshotSelected(const QRect& rect);

signals:
    // 开始自定义截图
    void __startScreenshot();

private:
    // 截图遮罩窗口
    SEOverlayWidget* m_overlayWidget;
    // 屏幕原始图像
    QPixmap m_screenPixmap;
    // 截图结果
    QPixmap m_resultPixmap;
};

