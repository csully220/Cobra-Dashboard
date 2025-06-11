#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QImage>

// Added
#include <QBrush>
#include <QFont>
#include <QPen>

class CGaugeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CGaugeWidget(QWidget *parent = nullptr);
    void paint(QPainter *painter, QPaintEvent *event);

    QPoint Location() const;
    void setLocation(QPoint newLocation);

    void commandNeedlePosition(qreal position);

    qreal m_lower_bound;
    qreal m_upper_bound;

    qreal m_tolerance;

signals:

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    bool moveRequired();
    bool m_new_p_cmd;

    QImage m_bg_img;
    qreal m_p;       // needle position (angle)
    qreal m_p_start; // starting position at time of command (angle)
    qreal m_p_cmd;   // commanded position (angle)
    qreal m_v;       // needle angle rate of change
    qreal m_a;       // needle angle accelation

    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

    QPoint m_Location;
};

#endif // GAUGEWIDGET_H
