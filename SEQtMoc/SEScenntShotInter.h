#pragma once
class SEScenntShotInter : public QObject
{
	Q_OBJECT
public:
	SEScenntShotInter(QObject* parent = nullptr);
	virtual ~SEScenntShotInter() = default;

public:
    // 开始截图操作
    virtual void startScreenshot() = 0;

signals:
	/*截图结束，传回截图*/
	void endScreenshot(QPixmap _screenPixmap);

};

