#pragma once
class SEOverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SEOverlayWidget(const QPixmap& bg, QWidget* parent = nullptr);

signals:
    void selectionFinished(const QRect& rect);

protected:
    /*��갴���¼�*/
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_background;//������ȫ����ͼ��
    QRect m_selectionRect;//ѡ�������
    QPoint m_startPos;//��갴�����
    QPoint m_endPos;
    enActionType m_enType = enActionType::enNone;
};

