#pragma once
class SEOverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SEOverlayWidget(const QPixmap& bg, QWidget* parent = nullptr);

signals:
    void selectionFinished(const QRect& rect);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_background;
    QPoint m_startPos;
    QPoint m_endPos;
    bool m_selecting = false;
};

