#include "uglylabel.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
UglyLabel::UglyLabel(QWidget *parent,QString label)
    :
    QWidget(parent),
    label(label)
{
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    this->setLable(label);

}



void UglyLabel::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int rectWidth = this->width();
    int rectHeight = this->height();
    int subRectForEdgesWidth = rectWidth/4;
    int subRectForEdgesHeigth = /*subRectForEdgesWidth;*/rectHeight/2;
    QRect rectTooThinLeft(1,0,rectHeight,rectHeight);
    QRect rectTooThinRight(rectWidth-rectHeight,0,rectHeight-1,rectHeight);

    if(fillLabel){
        painter.setBrush(QColor(12,255,154,255));
        painter.drawPie(rectTooThinLeft, 1440, 2880);
        //painter.drawPie(rectTooThinLeft, 2880-80, 1440-80);
        painter.drawPie(rectTooThinRight, 1440, -2880);
        //painter.drawPie(rectTooThinRight, 1440-80, -1440+80);
        painter.fillRect(QRect(rectHeight/2-1,0,rectWidth-rectHeight+2,(rectHeight*2)),QColor(12,255,154,255));
        painter.setPen(QColor(12,255,154,255));

        painter.drawLine(12,0,rectWidth-12,0);
        painter.drawLine(11,rectHeight,rectWidth-12,rectHeight);
        painter.setPen(QColor(255,255,255,255));
        painter.drawText(7,17,label);
    } else {
        painter.setPen(QColor(12,255,154,255));
        painter.drawArc(rectTooThinLeft, 1440+80, 1440-80);
        painter.drawArc(rectTooThinLeft, 2880-80, 1440-80);
        painter.drawArc(rectTooThinRight, -1440+80, 1440-80);
        painter.drawArc(rectTooThinRight, 1440-80, -1440+80);
        painter.drawLine(12,0,rectWidth-12,0);
        painter.drawLine(11,rectHeight,rectWidth-12,rectHeight);
        painter.drawText(7,17,label);

    }


}

void UglyLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //qDebug() << "Left mouse button pressed.";
        QPointF p = event->position();
        mouseCordinatesInsideWidget = p.toPoint();
        holdingLeftMouse = true; // Example action
        repaint();
    }
}
void UglyLabel::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        holdingLeftMouse = false;
        repaint();
    }
}

void UglyLabel::mouseMoveEvent(QMouseEvent *event)
{

    QPointF p = event->position();
    QPoint p1 = p.toPoint();
    QPoint globalPos = mapToGlobal(p1);
    QPoint ParentsCoordinates = mapToParent(p1);
    qInfo() << "Outside the widget aka parent" << "x: "<< ParentsCoordinates.x() << "y: " << ParentsCoordinates.y();
    qInfo() << "Inside the widget" << "x: " << p1.x() << "y: " << p1.y();
    fillLabel = true;
    if(holdingLeftMouse && this->parentWidget()->inherits("MainWindow")){
        absoulteX = ParentsCoordinates.x() - mouseCordinatesInsideWidget.x();
        absoulteY = ParentsCoordinates.y() - mouseCordinatesInsideWidget.y();
        x1 = absoulteX;
        y1 = absoulteY;
        repaint();
    } else if (holdingLeftMouse && this->parentWidget()->inherits("LabelBar")){
        absoulteX = ParentsCoordinates.x() - mouseCordinatesInsideWidget.x();

        x1 = absoulteX;
        if(x1 < 0){
            x1 = 0;
        }
        if(x1 + x2 > this->parentWidget()->width()){
            x1 = this->parentWidget()->width() - x2;
        }
        qInfo() << "x1: " << x1 << "ParentWidget: " << parentWidget()->width();
        if(x1 > this->parentWidget()->width()){
            x1 = this->parentWidget()->width() - x2;
        }

        repaint();
    }

    repaint();

}


void UglyLabel::enterEvent(QEnterEvent *event)
{
   // qInfo() << "Entered";

    fillLabel = true;
    repaint();
}

void UglyLabel::leaveEvent(QEvent *event)
{
    //qInfo() << "Bye";
    fillLabel = false;
    repaint();
}


void UglyLabel::setLable(QString label){
    if(!label.isNull()){
        QFont font = this->font();
        QFontMetrics metrics(font);
        int width = metrics.horizontalAdvance(label);

        x2 = width + 14;
        if(x2 < 35)
            x2 = 35;
    } else if (label.isNull() || label == ""){
        x2 = 35;
    }
}


