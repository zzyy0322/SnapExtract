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
		// 1. 初始化 OCR 引擎：参数1=NULL（默认路径），参数2=语言包（chi_sim=中文，eng=英文，可叠加如"chi_sim+eng"）
		// 2. 语言包路径：默认会找 Tesseract 安装目录的 share/tessdata，若找不到需手动指定（如 m_tessApi->Init("D:/Tesseract/share/tessdata", "chi_sim")）
		if (g_tessApi->Init("D:/Project/SnapExtract/Tesseract/traineddata", "chi_sim+eng") != 0) {
			qCritical() << "[OCR 错误] Tesseract 引擎初始化失败！请检查语言包是否存在。";
			return;
		}

		// （可选）设置识别模式（如仅识别文本，忽略图片中的表格/公式）
		g_tessApi->SetPageSegMode(tesseract::PSM_AUTO);  // 自动分页模式（适合截图这种单区域文本）
	}

	Pix* __preprocessImage(const QImage& qImage)
	{
		if (qImage.isNull()) return nullptr;

		// 1. QImage 转为灰度图（Leptonica 处理灰度图效率更高，识别率更好）
		QImage grayImage = qImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[预处理错误] 彩色图转灰度图失败！";
			return nullptr;
		}

		// 2. 灰度图转为 Leptonica 的 Pix 格式（8位灰度图，深度=8）
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[预处理错误] 创建 Pix 图像失败！";
			return nullptr;
		}

		// 3. 复制 QImage 像素数据到 Pix（注意内存对齐，Leptonica Pix 每行像素按 4 字节对齐）
		for (int y = 0; y < grayImage.height(); y++) {
			// 获取 QImage 第 y 行的像素数据
			uchar* qImageLine = grayImage.scanLine(y);
			// 获取 Pix 第 y 行的像素数据（pixGetData 是 Pix 的数据首地址，pixGetWpl 是每行的字节数）
			uchar* pixLine = reinterpret_cast<uchar*>(pixGetData(pix)) + y * pixGetWpl(pix);
			// 复制数据（灰度图每行像素数 = 图像宽度，直接 memcpy）
			memcpy(pixLine, qImageLine, grayImage.width());
		}

		// 4. （可选）二值化处理（进一步去除噪声，适合文字识别：像素值 > 128 设为白色，否则黑色）
		Pix* pixBinary = pixThresholdToBinary(pix, 128);

		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "预处理后的图像已保存到 D:/preprocessed_binary.png";

		pixDestroy(&pix);  // 释放原灰度图 Pix
		return pixBinary;
	}

	QString __ocrRecognize(Pix* pixImage)
	{
		if (pixImage == nullptr || g_tessApi == nullptr) {
			return "[识别错误] 图像为空或 OCR 引擎未初始化！";
		}

		int width = pixGetWidth(pixImage);
		int height = pixGetHeight(pixImage);

		// 1. 设置待识别的 Pix 图像
		g_tessApi->SetImage(pixImage);

		// 2. 执行 OCR 识别（获取 UTF-8 格式的结果）
		char* ocrResult = g_tessApi->GetUTF8Text();
		QString result = QString::fromUtf8(ocrResult);

#if 0
		// 3. （可选）获取识别置信度（判断识别结果是否可靠，0=完全不可靠，100=完全可靠）
		int confidence = g_tessApi->MeanTextConfidence();
		qInfo() << "[OCR 识别完成] 置信度：" << confidence << "%";
#endif // 0

		// 4. 释放资源（必须手动释放，避免内存泄漏）
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
		qCritical() << "preprocessImage: 输入图像为空！";
		return nullptr;
	}

	qInfo() << "preprocessImage: 输入图像尺寸" << qImage.width() << "x" << qImage.height();

	QString ocrResult = QString();

	Pix* preprocessedPix = __preprocessImage(qImage);
	if (preprocessedPix == nullptr) {
		return ocrResult;
	}

	// 2. 执行 OCR 识别
	ocrResult = __ocrRecognize(preprocessedPix);
	return ocrResult;
}

