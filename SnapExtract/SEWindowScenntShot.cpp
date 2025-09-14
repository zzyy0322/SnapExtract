#include "pch.h"
#include "SEWindowScenntShot.h"

SEWindowScenntShot::SEWindowScenntShot(QObject* parent) :
	SEScenntShotInter(parent)
{
}

SEWindowScenntShot::~SEWindowScenntShot()
{
	if (m_overlayWidget != nullptr)
	{
		m_overlayWidget->deleteLater();
		m_overlayWidget = nullptr;
	}
}

void SEWindowScenntShot::startScreenshot()
{
	// 1. 获取当前全屏截图（包含所有可见窗口和桌面）
	// grabWindow(0) 表示捕获整个屏幕（0 是桌面窗口的句柄）
	m_screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);	
	if (m_screenPixmap.isNull()) {
		qWarning() << "Failed to capture screen!";
		return;
	}

	// 2. 创建并配置覆盖层窗口（用户选择区域的交互界面）
	// 先销毁可能存在的旧覆盖层
	if (m_overlayWidget) {
		m_overlayWidget->deleteLater();
	}
	m_overlayWidget = new SEOverlayWidget(m_screenPixmap);
	// 设置覆盖层大小为屏幕大小，确保全屏覆盖
	m_overlayWidget->setGeometry(QGuiApplication::primaryScreen()->geometry());
	// 显示为全屏窗口（无标题栏，覆盖所有内容）
	m_overlayWidget->showFullScreen();

	if (m_overlayWidget)
	{
		connect(m_overlayWidget, &SEOverlayWidget::selectionFinished,
			this, &SEWindowScenntShot::onScreenshotSelected);
	}
}

void SEWindowScenntShot::onScreenshotSelected(const QRect& rect)
{
	// 清理资源：隐藏并销毁覆盖层窗口
	if (m_overlayWidget) {
		m_overlayWidget->hide();
		m_overlayWidget->deleteLater(); // 延迟销毁，避免界面卡顿
		m_overlayWidget = nullptr;
	}

	// 1. 从全屏截图中裁剪用户选择的区域
	// 注意：rect 是用户在覆盖层上选择的区域，坐标与屏幕一致
	/*获取当前系统的分辨率*/
	qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
	QRect sourceRect(
		rect.x() * dpr,       // x坐标转换
		rect.y() * dpr,       // y坐标转换
		rect.width() * dpr,   // 宽度转换
		rect.height() * dpr   // 高度转换
	);
	QPixmap selectedPixmap = m_screenPixmap.copy(sourceRect);

	/*在预览中显示当前图片*/
	emit endScreenshot(selectedPixmap);

#if 0
	// 2. 处理裁剪后的截图
	// 2.1 复制到系统剪贴板
	QClipboard* clipboard = QGuiApplication::clipboard();
	clipboard->setPixmap(selectedPixmap);

	// 2.2 弹出保存文件对话框（可选功能，根据需求开启）
	QString defaultFileName = QString("screenshot_%1.png")
		.arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
	QString filePath = QFileDialog::getSaveFileName(
		nullptr, "Save Screenshot", defaultFileName, "PNG Images (*.png);;All Files (*)"
	);
	if (!filePath.isEmpty()) {
		bool saved = selectedPixmap.save(filePath);
	}
#endif // 0
}
