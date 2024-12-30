#ifndef BOOKBARLABELSFOROPENDBOOKS_H
#define BOOKBARLABELSFOROPENDBOOKS_H

#include <QWidget>

class BookBarLabelsForOpendBooks : public QWidget
{
    Q_OBJECT
public:
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 25;
    int absoluteX = 0, absoluteY = 0;
    QPoint mouseCordinatesInsideWidget; /* you need this so your labelwidget doesnt move to make your mouse always stay topleft making
    it look ugly but stays where you clicked (if you clicked in the middle your mouse stays in the middle) you calculate the absolute positions - relative position
    (x and y of the mouse inside the main window - x and y of the mouse inside the the widget) */
    QString label;
    explicit BookBarLabelsForOpendBooks(QWidget *parent = nullptr,QString label = NULL);
    void paintEvent(QPaintEvent * event) override;
    void enterEvent(QEnterEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void setLable(QString label = NULL);


private:


    bool fillLabel = false;
    bool holdingLeftMouse = false;
signals:
};

#endif // BOOKBARLABELSFOROPENDBOOKS_H
