#pragma once
class SEScenntShotInter : public QObject
{
	Q_OBJECT
public:
	SEScenntShotInter(QObject* parent = nullptr);
	virtual ~SEScenntShotInter() = default;

public:
    // ¿ªÊ¼½ØÍ¼²Ù×÷
    virtual void startScreenshot() = 0;
};

