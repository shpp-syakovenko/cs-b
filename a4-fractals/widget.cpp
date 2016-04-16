#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("a4-fractal");
    this->setFixedSize(640,480);

    labelSerp = new QLabel(this);
    labelSerp->setText("<h2 style='color:red'>Tреугольник Серпинского</h2>");
    labelSerp->setGeometry(220,-40,250,100);
    labelSerp->show();
}

// draw "Tреугольник Серпинского"
void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPoint *point = new QPoint(320,50);

        for(int i = 0; i < 50000; i++){
            moveRandom(point);
            drawRectangle(point->x(), point->y());
        }
}

// We calculate the coordinates of the rectangle
void Widget::moveRandom(QPoint *point){
    QPoint desk = randConer();

    int x = (point->x() + desk.x()) / 2;
    int y = (point->y() + desk.y()) / 2;

    point->setX(x);
    point->setY(y);

}

// Choose a random corner of the triangle
QPoint Widget::randConer(){
    int coner = (rand() % 3) + 1;
    if(coner == 1){
        QPoint point;
        point.setX(320);
        point.setY(50);
        return point;
    }else if(coner == 2){
        QPoint point;
        point.setX(0);
        point.setY(440);
        return point;
    }else{
        QPoint point;
        point.setX(640);
        point.setY(440);
        return point;

    }
}

// draw rectangle size in the 1 pixel.
void Widget::drawRectangle(int x, int y){
    painter = new QPainter(this);
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter->drawRect(x,y,1,1);
}

Widget::~Widget()
{
    delete ui;
}
