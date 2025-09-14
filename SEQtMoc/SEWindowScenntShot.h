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
	// ͨ�� SEScenntShotInter �̳�
	void startScreenshot() override;

private slots:
    void onScreenshotSelected(const QRect& rect);

signals:
    // ��ʼ�Զ����ͼ
    void __startScreenshot();

private:
    // ��ͼ���ִ���
    SEOverlayWidget* m_overlayWidget;
    // ��Ļԭʼͼ��
    QPixmap m_screenPixmap;
    // ��ͼ���
    QPixmap m_resultPixmap;
};

