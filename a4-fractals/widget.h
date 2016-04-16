#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    QPainter *painter;
    QLabel *labelSerp;

    QPoint randConer();
    void moveRandom(QPoint *point);
    void drawRectangle(int x, int y);

};

#endif // WIDGET_H
