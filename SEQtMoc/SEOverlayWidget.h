#pragma once
class SEOverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SEOverlayWidget(const QPixmap& bg, QWidget* parent = nullptr);

signals:
    void selectionFinished(const QRect& rect);

protected:
    /*鼠标按下事件*/
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_background;//背景（全屏截图）
    QRect m_selectionRect;//选择的区域
    QPoint m_startPos;//鼠标按下起点
    QPoint m_endPos;
    enActionType m_enType = enActionType::enNone;
};

