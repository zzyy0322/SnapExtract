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

		// 单行文字识别模式
		//g_tessApi->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
		// （可选）设置识别模式（如仅识别文本，忽略图片中的表格/公式）
		g_tessApi->SetPageSegMode(tesseract::PSM_AUTO);  // 自动分页模式（适合截图这种单区域文本）

		g_tessApi->SetVariable("debug_file", "tesseract_debug.log");
		g_tessApi->SetVariable("tessedit_debug_ocr", "1");
	}

#if 0
	Pix* __preprocessImage(const QImage& qImage)
	{
		if (qImage.isNull()) return nullptr;

		// 1. 检查并调整图像大小（确保足够大，Tesseract对小图像识别效果差）
		QImage scaledImage = qImage;
		if (scaledImage.width() < 300 || scaledImage.height() < 50) {
			// 按比例放大，确保宽度至少300像素
			double scale = qMax(300.0 / scaledImage.width(), 1.0);
			scaledImage = scaledImage.scaled(
				scaledImage.width() * scale,
				scaledImage.height() * scale,
				Qt::KeepAspectRatio,
				Qt::SmoothTransformation // 平滑缩放，避免锯齿
			);
			qInfo() << "图像已放大至：" << scaledImage.width() << "x" << scaledImage.height();
		}

		// 2. QImage 转为灰度图
		QImage grayImage = scaledImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[预处理错误] 彩色图转灰度图失败！";
			return nullptr;
		}

		// 3. 灰度图转为 Leptonica 的 Pix 格式（8位灰度图）
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[预处理错误] 创建 Pix 图像失败！";
			return nullptr;
		}
		pixWrite("D:/preprocessed_gray.png", pix, IFF_PNG); // 保存灰度图用于调试

		// 4. 正确复制像素数据（处理 Leptonica 的 4 字节对齐问题）
		l_int32 wpl = pixGetWpl(pix); // 获取每行的 32 位字数量
		l_uint32* data = pixGetData(pix); // 获取 Pix 的数据指针（32位字指针）

		for (int y = 0; y < grayImage.height(); y++) {
			uchar* qImageLine = grayImage.scanLine(y); // QImage 行数据（8位）
			l_uint32* pixLine = data + y * wpl; // Pix 行数据（32位字）

			// 逐字节复制，处理对齐差异（关键修复）
			for (int x = 0; x < grayImage.width(); x++) {
				// 将 8 位灰度值放入 32 位字的对应位置
				pixLine[x >> 2] &= ~(0xff << ((x & 3) << 3));
				pixLine[x >> 2] |= (qImageLine[x] << ((x & 3) << 3));
			}
		}

		// 5. 优化二值化处理（使用自适应阈值替代固定阈值）
		Pix* pixBinary = nullptr;
		// 4. 二值化（使用你的接口，仅需传入图像和阈值）
		// 注意：阈值需要根据实际图像调整（建议80-150之间测试）
		l_int32 threshold = 100; // 可根据效果调整
		pixBinary = pixThresholdToBinary(pix, threshold);

		// 6. 去除孤立噪声点（进一步优化图像）
		//Pix* pixClean = pixRemoveSpeckles(pixBinary, 2, 2, 2, 2);
		//pixDestroy(&pixBinary);
		//pixBinary = pixClean;

		// 保存处理后的图像用于调试
		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "预处理后的图像已保存到 D:/preprocessed_binary.png";

		pixDestroy(&pix);  // 释放原灰度图 Pix
		return pixBinary;
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
#endif // 0

	Pix* __preprocessImage(const QImage& qImage)
	{
		if (true)
		{
			Pix* image = pixRead("D:/original_screenshot.png");
			return image;
		}

		if (qImage.isNull()) return nullptr;

		// 1. 转为灰度图
		QImage grayImage = qImage.convertToFormat(QImage::Format_Grayscale8);
		if (grayImage.isNull()) {
			qCritical() << "[预处理失败] 彩色图转灰度图失败";
			return nullptr;
		}

		// 2. 创建Leptonica的Pix对象（8位灰度图）
		Pix* pix = pixCreate(grayImage.width(), grayImage.height(), 8);
		if (pix == nullptr) {
			qCritical() << "[预处理失败] 创建Pix图像失败";
			return nullptr;
		}

		// 3. 填充灰度数据（关键修复：用memcpy直接复制，避免位运算错误）
		for (int y = 0; y < grayImage.height(); y++) {
			uchar* qImageLine = grayImage.scanLine(y); // QImage的灰度数据（8位/像素）
			uchar* pixLine = reinterpret_cast<uchar*>(pixGetData(pix)) + y * pixGetWpl(pix) * 4;
			// 注意：pixGetWpl返回的是32位整数的行数，乘以4得到字节数
			memcpy(pixLine, qImageLine, grayImage.width()); // 直接复制一行数据
		}

		// 修复：填充数据后再保存灰度图（此时才是正确的灰度数据）
		pixWrite("D:/preprocessed_gray.png", pix, IFF_PNG);
		qInfo() << "灰度图已保存至 D:/preprocessed_gray.png";

		// 4. 二值化（调整阈值适配你的图像，建议80-150之间测试）
		l_int32 threshold = 128; // 可根据实际图像明暗调整
		Pix* pixBinary = pixThresholdToBinary(pix, threshold);

		//5. 可选：去除噪点（如果二值化后有杂点）
		//Pix* pixClean = pixRemoveSpeckles(pixBinary, 2, 2, 2, 2);
		//pixDestroy(&pixBinary);
		//pixBinary = pixClean;

	   // 保存二值化图
		pixWrite("D:/preprocessed_binary.png", pixBinary, IFF_PNG);
		qInfo() << "二值化图已保存至 D:/preprocessed_binary.png";

		pixDestroy(&pix); // 释放原灰度图
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
		if (ocrResult != nullptr)
		{
			std::cout << "Tesseract 原始识别结果：" << ocrResult << std::endl;

			std::string str(ocrResult);
			QString result = QString::fromStdString(str);
			delete[] ocrResult;
			return result;
		}

#if 0
		// 3. （可选）获取识别置信度（判断识别结果是否可靠，0=完全不可靠，100=完全可靠）
		int confidence = g_tessApi->MeanTextConfidence();
		qInfo() << "[OCR 识别完成] 置信度：" << confidence << "%";
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

