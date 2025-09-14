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
	// 1. ��ȡ��ǰȫ����ͼ���������пɼ����ں����棩
	// grabWindow(0) ��ʾ����������Ļ��0 �����洰�ڵľ����
	m_screenPixmap = QGuiApplication::primaryScreen()->grabWindow(0);	
	if (m_screenPixmap.isNull()) {
		qWarning() << "Failed to capture screen!";
		return;
	}

	// 2. ���������ø��ǲ㴰�ڣ��û�ѡ������Ľ������棩
	// �����ٿ��ܴ��ڵľɸ��ǲ�
	if (m_overlayWidget) {
		m_overlayWidget->deleteLater();
	}
	m_overlayWidget = new SEOverlayWidget(m_screenPixmap);
	// ���ø��ǲ��СΪ��Ļ��С��ȷ��ȫ������
	m_overlayWidget->setGeometry(QGuiApplication::primaryScreen()->geometry());
	// ��ʾΪȫ�����ڣ��ޱ������������������ݣ�
	m_overlayWidget->showFullScreen();

	if (m_overlayWidget)
	{
		connect(m_overlayWidget, &SEOverlayWidget::selectionFinished,
			this, &SEWindowScenntShot::onScreenshotSelected);
	}
}

void SEWindowScenntShot::onScreenshotSelected(const QRect& rect)
{
	// ������Դ�����ز����ٸ��ǲ㴰��
	if (m_overlayWidget) {
		m_overlayWidget->hide();
		m_overlayWidget->deleteLater(); // �ӳ����٣�������濨��
		m_overlayWidget = nullptr;
	}

	// 1. ��ȫ����ͼ�вü��û�ѡ�������
	// ע�⣺rect ���û��ڸ��ǲ���ѡ���������������Ļһ��
	/*��ȡ��ǰϵͳ�ķֱ���*/
	qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
	QRect sourceRect(
		rect.x() * dpr,       // x����ת��
		rect.y() * dpr,       // y����ת��
		rect.width() * dpr,   // ���ת��
		rect.height() * dpr   // �߶�ת��
	);
	QPixmap selectedPixmap = m_screenPixmap.copy(sourceRect);

	/*��Ԥ������ʾ��ǰͼƬ*/
	emit endScreenshot(selectedPixmap);

#if 0
	// 2. ����ü���Ľ�ͼ
	// 2.1 ���Ƶ�ϵͳ������
	QClipboard* clipboard = QGuiApplication::clipboard();
	clipboard->setPixmap(selectedPixmap);

	// 2.2 ���������ļ��Ի��򣨿�ѡ���ܣ�������������
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
