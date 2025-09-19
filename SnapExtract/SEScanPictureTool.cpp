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

		// ��������ʶ��ģʽ
		//g_tessApi->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
		// ����ѡ������ʶ��ģʽ�����ʶ���ı�������ͼƬ�еı��/��ʽ��
		g_tessApi->SetPageSegMode(tesseract::PSM_AUTO);  // �Զ���ҳģʽ���ʺϽ�ͼ���ֵ������ı���

		g_tessApi->SetVariable("debug_file", "tesseract_debug.log");
		g_tessApi->SetVariable("tessedit_debug_ocr", "1");
	}

#if 0
	Pix* __preprocessImage(const QImage& qImage)
	{
		if (qImage.isNull()) return nullptr;

		// 1. ��鲢����ͼ���С��ȷ���㹻��Tesseract��Сͼ��ʶ��Ч���
		QImage scaledImage = qImage;
		if (scaledImage.width() < 300 || scaledImage.height() < 50) {
			// �������Ŵ�ȷ���������300����
			double scale = qMax(300.0 / scaledImage.width(), 1.0);
			scaledImage = scaledImage.scaled(
				scaledImage.width() * scale,
				scaledImage.height() * scale,
				Qt::KeepAspectRatio,
				Qt::SmoothTransformation // ƽ�����ţ�������
			);
			qInfo() << "ͼ���ѷŴ�����" << scaledImage.width() << "x" << scaledImage.height();
		}

		// 2. QImage תΪ�Ҷ�ͼ
		QImage grayImage = scaledImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[Ԥ�������] ��ɫͼת�Ҷ�ͼʧ�ܣ�";
			return nullptr;
		}

		// 3. �Ҷ�ͼתΪ Leptonica �� Pix ��ʽ��8λ�Ҷ�ͼ��
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[Ԥ�������] ���� Pix ͼ��ʧ�ܣ�";
			return nullptr;
		}
		pixWrite("D:/preprocessed_gray.png", pix, IFF_PNG); // ����Ҷ�ͼ���ڵ���

		// 4. ��ȷ�����������ݣ����� Leptonica �� 4 �ֽڶ������⣩
		l_int32 wpl = pixGetWpl(pix); // ��ȡÿ�е� 32 λ������
		l_uint32* data = pixGetData(pix); // ��ȡ Pix ������ָ�루32λ��ָ�룩

		for (int y = 0; y < grayImage.height(); y++) {
			uchar* qImageLine = grayImage.scanLine(y); // QImage �����ݣ�8λ��
			l_uint32* pixLine = data + y * wpl; // Pix �����ݣ�32λ�֣�

			// ���ֽڸ��ƣ����������죨�ؼ��޸���
			for (int x = 0; x < grayImage.width(); x++) {
				// �� 8 λ�Ҷ�ֵ���� 32 λ�ֵĶ�Ӧλ��
				pixLine[x >> 2] &= ~(0xff << ((x & 3) << 3));
				pixLine[x >> 2] |= (qImageLine[x] << ((x & 3) << 3));
			}
		}

		// 5. �Ż���ֵ������ʹ������Ӧ��ֵ����̶���ֵ��
		Pix* pixBinary = nullptr;
		// 4. ��ֵ����ʹ����Ľӿڣ����贫��ͼ�����ֵ��
		// ע�⣺��ֵ��Ҫ����ʵ��ͼ�����������80-150֮����ԣ�
		l_int32 threshold = 100; // �ɸ���Ч������
		pixBinary = pixThresholdToBinary(pix, threshold);

		// 6. ȥ�����������㣨��һ���Ż�ͼ��
		//Pix* pixClean = pixRemoveSpeckles(pixBinary, 2, 2, 2, 2);
		//pixDestroy(&pixBinary);
		//pixBinary = pixClean;

		// ���洦����ͼ�����ڵ���
		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "Ԥ������ͼ���ѱ��浽 D:/preprocessed_binary.png";

		pixDestroy(&pix);  // �ͷ�ԭ�Ҷ�ͼ Pix
		return pixBinary;
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
#endif // 0

	Pix* __preprocessImage(const QImage& qImage)
	{
		if (true)
		{
			Pix* image = pixRead("D:/original_screenshot.png");
			return image;
		}

		if (qImage.isNull()) return nullptr;

		// 1. תΪ�Ҷ�ͼ
		QImage grayImage = qImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[Ԥ����ʧ��] ��ɫͼת�Ҷ�ͼʧ��";
			return nullptr;
		}

		// 2. ����Leptonica��Pix����8λ�Ҷ�ͼ��
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[Ԥ����ʧ��] ����Pixͼ��ʧ��";
			return nullptr;
		}

		// 3. ���Ҷ����ݣ��ؼ��޸�����memcpyֱ�Ӹ��ƣ�����λ�������
		for (int y = 0; y < grayImage.height(); y++) {
			uchar* qImageLine = grayImage.scanLine(y); // QImage�ĻҶ����ݣ�8λ/���أ�
			uchar* pixLine = reinterpret_cast<uchar*>(pixGetData(pix)) + y * pixGetWpl(pix) * 4;
			// ע�⣺pixGetWpl���ص���32λ����������������4�õ��ֽ���
			memcpy(pixLine, qImageLine, grayImage.width()); // ֱ�Ӹ���һ������
		}

		// �޸���������ݺ��ٱ���Ҷ�ͼ����ʱ������ȷ�ĻҶ����ݣ�
		pixWrite("D:/preprocessed_gray.png", pix, IFF_PNG);
		qInfo() << "�Ҷ�ͼ�ѱ����� D:/preprocessed_gray.png";

		// 4. ��ֵ����������ֵ�������ͼ�񣬽���80-150֮����ԣ�
		l_int32 threshold = 128; // �ɸ���ʵ��ͼ����������
		Pix* pixBinary = pixThresholdToBinary(pix, threshold);

		//5. ��ѡ��ȥ����㣨�����ֵ�������ӵ㣩
		//Pix* pixClean = pixRemoveSpeckles(pixBinary, 2, 2, 2, 2);
		//pixDestroy(&pixBinary);
		//pixBinary = pixClean;

	   // �����ֵ��ͼ
		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "��ֵ��ͼ�ѱ����� D:/preprocessed_binary.png";

		pixDestroy(&pix); // �ͷ�ԭ�Ҷ�ͼ
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
		if (ocrResult != nullptr)
		{
			std::cout << "Tesseract ԭʼʶ������" << ocrResult << std::endl;

			std::string str(ocrResult);
			QString result = QString::fromStdString(str);
			delete[] ocrResult;
			return result;
		}

#if 0
		// 3. ����ѡ����ȡʶ�����Ŷȣ��ж�ʶ�����Ƿ�ɿ���0=��ȫ���ɿ���100=��ȫ�ɿ���
		int confidence = g_tessApi->MeanTextConfidence();
		qInfo() << "[OCR ʶ�����] ���Ŷȣ�" << confidence << "%";
#endif // 0
		return "None";
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

