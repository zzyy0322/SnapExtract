#include "pch.h"
#include "SEScanPictureTool.h"
#include "Leptonica/allheaders.h"
#include "tesseract/baseapi.h"
#include "tesseract/resultiterator.h"

namespace {

	tesseract::TessBaseAPI* g_tessApi = nullptr;

	void InitTesseract() 
	{
		if (g_tessApi != nullptr) {
			delete g_tessApi;
			g_tessApi = nullptr;
		}

		g_tessApi = new tesseract::TessBaseAPI();
		// 1. ��ʼ�� OCR ���棺����1=NULL��Ĭ��·����������2=���԰���chi_sim=���ģ�eng=Ӣ�ģ��ɵ�����"chi_sim+eng"��
		// 2. ���԰�·����Ĭ�ϻ��� Tesseract ��װĿ¼�� share/tessdata�����Ҳ������ֶ�ָ������ m_tessApi->Init("D:/Tesseract/share/tessdata", "chi_sim")��
		if (g_tessApi->Init("D:/Project/SnapExtract/Tesseract/traineddata", "chi_sim+eng") != 0) {
			qCritical() << "[OCR ����] Tesseract �����ʼ��ʧ�ܣ��������԰��Ƿ���ڡ�";
			return;
		}

		// ����ѡ������ʶ��ģʽ�����ʶ���ı�������ͼƬ�еı��/��ʽ��
		g_tessApi->SetPageSegMode(tesseract::PSM_AUTO);  // �Զ���ҳģʽ���ʺϽ�ͼ���ֵ������ı���
	}

	Pix* __preprocessImage(const QImage& qImage)
	{
		if (qImage.isNull()) return nullptr;

		// 1. QImage תΪ�Ҷ�ͼ��Leptonica ����Ҷ�ͼЧ�ʸ��ߣ�ʶ���ʸ��ã�
		QImage grayImage = qImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[Ԥ�������] ��ɫͼת�Ҷ�ͼʧ�ܣ�";
			return nullptr;
		}

		// 2. �Ҷ�ͼתΪ Leptonica �� Pix ��ʽ��8λ�Ҷ�ͼ�����=8��
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[Ԥ�������] ���� Pix ͼ��ʧ�ܣ�";
			return nullptr;
		}

		// 3. ���� QImage �������ݵ� Pix��ע���ڴ���룬Leptonica Pix ÿ�����ذ� 4 �ֽڶ��룩
		for (int y = 0; y < grayImage.height(); y++) {
			// ��ȡ QImage �� y �е���������
			uchar* qImageLine = grayImage.scanLine(y);
			// ��ȡ Pix �� y �е��������ݣ�pixGetData �� Pix �������׵�ַ��pixGetWpl ��ÿ�е��ֽ�����
			uchar* pixLine = reinterpret_cast<uchar*>(pixGetData(pix)) + y * pixGetWpl(pix);
			// �������ݣ��Ҷ�ͼÿ�������� = ͼ���ȣ�ֱ�� memcpy��
			memcpy(pixLine, qImageLine, grayImage.width());
		}

		// 4. ����ѡ����ֵ��������һ��ȥ���������ʺ�����ʶ������ֵ > 128 ��Ϊ��ɫ�������ɫ��
		Pix* pixBinary = pixThresholdToBinary(pix, 128);

		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "Ԥ������ͼ���ѱ��浽 D:/preprocessed_binary.png";

		pixDestroy(&pix);  // �ͷ�ԭ�Ҷ�ͼ Pix
		return pixBinary;
	}

	QString __ocrRecognize(Pix* pixImage)
	{
		if (pixImage == nullptr || g_tessApi == nullptr) {
			return "[ʶ�����] ͼ��Ϊ�ջ� OCR ����δ��ʼ����";
		}

		int width = pixGetWidth(pixImage);
		int height = pixGetHeight(pixImage);

		// 1. ���ô�ʶ��� Pix ͼ��
		g_tessApi->SetImage(pixImage);

		// 2. ִ�� OCR ʶ�𣨻�ȡ UTF-8 ��ʽ�Ľ����
		char* ocrResult = g_tessApi->GetUTF8Text();
		QString result = QString::fromUtf8(ocrResult);

#if 0
		// 3. ����ѡ����ȡʶ�����Ŷȣ��ж�ʶ�����Ƿ�ɿ���0=��ȫ���ɿ���100=��ȫ�ɿ���
		int confidence = g_tessApi->MeanTextConfidence();
		qInfo() << "[OCR ʶ�����] ���Ŷȣ�" << confidence << "%";
#endif // 0

		// 4. �ͷ���Դ�������ֶ��ͷţ������ڴ�й©��
		delete[] ocrResult;
		return result;
	}
}

SEScanPictureTool::SEScanPictureTool()
{
	if (g_tessApi == nullptr)
		InitTesseract();
}

QString SEScanPictureTool::ocrRecognize(const QImage& qImage)
{
	if (qImage.isNull()) {
		qCritical() << "preprocessImage: ����ͼ��Ϊ�գ�";
		return nullptr;
	}

	qInfo() << "preprocessImage: ����ͼ��ߴ�" << qImage.width() << "x" << qImage.height();

	QString ocrResult = QString();

	Pix* preprocessedPix = __preprocessImage(qImage);
	if (preprocessedPix == nullptr) {
		return ocrResult;
	}

	// 2. ִ�� OCR ʶ��
	ocrResult = __ocrRecognize(preprocessedPix);
	return ocrResult;
}

