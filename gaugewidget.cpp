#include "gaugewidget.h"

#include <QPainter>
#include <QPaintEvent>



CGaugeWidget::CGaugeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_p = 0.0;
    m_p_cmd = 0.0;
    m_v = 0.0;
    m_a = 0.0;

    m_lower_bound = 0.12;
    m_upper_bound = 0.88;

    m_tolerance = 0.01;

    m_new_p_cmd = false;

    m_Location = QPoint(60,60);

    m_bg_img = QImage("..\\..\\data\\bg_fuel_new.png");

    setFixedSize(m_bg_img.size().height(), m_bg_img.size().width());
}



void CGaugeWidget::paint(QPainter *painter, QPaintEvent *event)
{
    //painter->fillRect(event->rect(), background);

    QPoint img_offset(0,0);
    painter->drawImage(img_offset, m_bg_img);

    int hht = m_bg_img.size().height() / 2;
    int wdt = m_bg_img.size().width() / 2;

    //painter->setBrush(circleBrush);
    //painter->setPen(circlePen);

    qreal new_p = (m_p * (m_upper_bound - m_lower_bound)) + m_lower_bound;

    qreal theta = M_PI * new_p;   // radians
    //qreal scale = 60.0;       // magnitude for drawing only

    //painter->translate(hht, wdt);
    qreal scaled_hht = (qreal)hht * 0.68;

    qreal p2x = qCos(theta) * scaled_hht;
    qreal p2y = qSin(theta) * scaled_hht;

    QPointF p1 = QPointF((qreal)wdt, (qreal)hht + 36.0);
    QPointF p2 = QPointF(((qreal)wdt) - p2x, ((qreal)hht) - p2y);

    //painter->drawEllipse(QRect(m_Location.x(), m_Location.y(),
    //                           scale, scale));

    QPen linePen(QColor(255,25,25,255));
    linePen.setWidth(10);
    painter->setPen(linePen);
    painter->save();
    painter->drawLine(p1, p2);

    painter->restore();
}



void CGaugeWidget::animate()
{
    update();  // calls paintEvent
}



void CGaugeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(moveRequired()) {
        if(m_new_p_cmd) {
            m_p_start = m_p;
            m_new_p_cmd = false;
        }

        qreal diff = 0.0;
        if(m_p_start < m_p_cmd)
            diff = m_p_cmd - m_p_start;
        else if(m_p_start > m_p_cmd)
            diff = m_p_start - m_p_cmd;

        m_a = (diff/2) - m_p;
        m_v += m_a/60.0;

        m_p += m_v;

    }
    else {
        m_p_start = m_p;
        m_p_cmd = m_p;
    }


    if(m_p >= 1.0) {
        m_p = 1.0;
    }
    else if(m_p <= 0.0) {
        m_p = 0.0;
    }


    qDebug() << m_p;

    paint(&painter, event);
    painter.end();
}



bool CGaugeWidget::moveRequired()
{
    if(abs(m_p_cmd - m_p) <= m_tolerance
        || abs(m_p - m_p_cmd) <= m_tolerance)
        return false;
    else
        return true;
}



QPoint CGaugeWidget::Location() const
{
    return m_Location;
}



void CGaugeWidget::setLocation(QPoint newLocation)
{
    m_Location = newLocation;
}



void CGaugeWidget::commandNeedlePosition(qreal _p)
{

    if(_p >= 1.0) {
        m_p_cmd = 1.0;
    }
    else if(_p <= 0.0) {
        m_p_cmd = 0.0;
    }
    else
        m_p_cmd = _p;

    m_new_p_cmd = true;
}
