#include "pch.h"
#include "SEOverlayWidget.h"
#include "SEScenntShotInter.h"

SEOverlayWidget::SEOverlayWidget(const QPixmap& bg, QWidget* parent):
	m_background(bg), QWidget(parent)
{
	// ���ô������ԣ��ޱ߿��ö�����͸��
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	m_selectionRect = QRect();
}

void SEOverlayWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_startPos = event->pos();
		// ��ʼ��ѡ���������ϽǺ����½Ǿ�Ϊ��ʼ�㣩
		m_selectionRect.setTopLeft(m_startPos);
		m_selectionRect.setBottomRight(m_startPos);
		m_selecting = true; // ��ǿ�ʼѡ��
	}

	QWidget::mousePressEvent(event);
}

void SEOverlayWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (m_selecting)
	{
		m_endPos = event->pos();
		m_selectionRect.setBottomRight(m_endPos);
		update(); // �����ػ棬ʵʱ��ʾѡ������
	}

	QWidget::mouseMoveEvent(event);
}

void SEOverlayWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_selecting) // ����ͷ�������ѡ��
	{
		m_selecting = false; // ����ѡ��
		// ��׼�����Σ�ȷ�����Ͻ�����С�����½ǣ����⸺����ת��
		m_selectionRect = m_selectionRect.normalized();
	}

	if (event->button() == Qt::RightButton && !m_selecting)
	{
		emit selectionFinished(m_selectionRect);
	}

	QWidget::mouseReleaseEvent(event);
}

void SEOverlayWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event); // �����¼�����
	QPainter painter(this); // ��������

	// 1. ���ư�͸����ɫ����������������Ļ��ͻ��ѡ������
	painter.fillRect(rect(), QColor(0, 0, 0, 100)); // ���һ��������͸���ȣ�0-255��

	// 2. ��ѡ���������ԭʼ��ͼ���γɡ��οա�Ч������ʾԭʼ���棩
	if (!m_selectionRect.isEmpty()) // ֻ��ѡ��������Чʱ�Ż���
	{
		// ��ȫ����ͼ��m_background���н�ȡѡ�����򣬻��Ƶ����ǲ���
		painter.drawPixmap(m_selectionRect, m_background, m_selectionRect);
	}

	// 3. ����ѡ������ĺ�ɫ�߿򣨱����û�ʶ��
	painter.setPen(QPen(Qt::red, 2)); // ��ɫ��2px��Ļ���
	painter.drawRect(m_selectionRect); // ���ƾ��α߿�
}
