#include "pch.h"
#include "SEOverlayWidget.h"
#include "SEScenntShotInter.h"

SEOverlayWidget::SEOverlayWidget(const QPixmap& bg, QWidget* parent):
	m_background(bg), QWidget(parent)
{
}

void SEOverlayWidget::mousePressEvent(QMouseEvent* event)
{
}

void SEOverlayWidget::mouseMoveEvent(QMouseEvent* event)
{
}

void SEOverlayWidget::mouseReleaseEvent(QMouseEvent* event)
{
}

void SEOverlayWidget::paintEvent(QPaintEvent* event)
{
}
