#pragma once
class SEScenntShotInter : public QObject
{
	Q_OBJECT
public:
	SEScenntShotInter(QObject* parent = nullptr);
	virtual ~SEScenntShotInter() = default;

public:
    // ��ʼ��ͼ����
    virtual void startScreenshot() = 0;
};

