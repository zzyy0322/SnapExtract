#pragma once
class SEScanPictureTool
{
public:
	SEScanPictureTool();

public:
	QString ocrRecognize(const QImage& qImage);
};

