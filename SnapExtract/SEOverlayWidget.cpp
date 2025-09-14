#include "pch.h"
#include "SEOverlayWidget.h"
#include "SEScenntShotInter.h"

SEOverlayWidget::SEOverlayWidget(const QPixmap& bg, QWidget* parent):
	m_background(bg), QWidget(parent)
{
	// 设置窗口属性：无边框、置顶、半透明
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	m_selectionRect = QRect();
	m_enType = enActionType::enSnapStart;
}

void SEOverlayWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_startPos = event->pos();
		// 初始化选择区域（左上角和右下角均为起始点）
		m_selectionRect.setTopLeft(m_startPos);
		m_selectionRect.setBottomRight(m_startPos);
		m_enType = enActionType::enSnaping;
	}

	if (event->button() == Qt::RightButton && m_enType == enActionType::enSnapEnd)
	{
		emit selectionFinished(m_selectionRect);
	}

	if (event->button() == Qt::RightButton)
	{
		SEOverlayWidget::close();
		emit selectionFinished(m_selectionRect);
	}

	QWidget::mousePressEvent(event);
}

void SEOverlayWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (m_enType == enActionType::enSnaping)
	{
		m_endPos = event->pos();
		m_selectionRect.setBottomRight(m_endPos);
		update(); // 触发重绘，实时显示选择区域
	}

	QWidget::mouseMoveEvent(event);
}

void SEOverlayWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_enType == enActionType::enSnaping) // 左键释放且正在选择
	{
		m_enType = enActionType::enSnapEnd;
	}

	QWidget::mouseReleaseEvent(event);
}

void SEOverlayWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event); // 忽略事件参数
	QPainter painter(this); // 创建画笔

	// 1. 绘制半透明黑色背景（覆盖整个屏幕，突出选择区域）
	painter.fillRect(rect(), QColor(0, 0, 0, 100)); // 最后一个参数是透明度（0-255）

	// 2. 在选择区域绘制原始截图（形成“镂空”效果，显示原始画面）
	if (!m_selectionRect.isEmpty()) // 只有选择区域有效时才绘制
	{
		/*获取当前系统的分辨率*/
		qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
		QRect sourceRect(
			m_selectionRect.x() * dpr,       // x坐标转换
			m_selectionRect.y() * dpr,       // y坐标转换
			m_selectionRect.width() * dpr,   // 宽度转换
			m_selectionRect.height() * dpr   // 高度转换
		);

		// 从全屏截图（m_background）中截取选择区域，绘制到覆盖层上
		painter.drawPixmap(m_selectionRect, m_background, sourceRect);
	}

	// 3. 绘制选择区域的红色边框（便于用户识别）
	painter.setPen(QPen(Qt::red, 2)); // 红色、2px宽的画笔
	painter.drawRect(m_selectionRect); // 绘制矩形边框
}
