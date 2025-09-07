#pragma once

#include "SEScenntShotInter.h"

class SEWindowScenntShot : public SEScenntShotInter
{
	Q_OBJECT
public:
	SEWindowScenntShot(QObject* parent = nullptr);

public:
	// ͨ�� SEScenntShotInter �̳�
	void startScreenshot() override;

private:
    // ��ͼ���ִ���
    QWidget* m_overlayWidget;
    // ��Ļԭʼͼ��
    QPixmap m_screenPixmap;
    // ��ǰѡ�е�����
    QRect m_selectedArea;
    // �Ƿ����ڽ�ͼ
    bool m_isCapturing;
};

