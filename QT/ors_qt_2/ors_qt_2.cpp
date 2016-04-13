#include "ors_qt_2.h"
#include "ui_ors_qt_2.h"
#include <rqt_gui_cpp/plugin.h>
#include <ros/macros.h>

ors_qt_2::ors_qt_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ors_qt_2),
    checkData(this),
    sub(n.subscribe("/turtle1/cmd_vel",10,&ors_qt_2::fetchData,this))
{
    QObject::connect(&checkData,SIGNAL(timeout()),this,SLOT(update()));
    ui->setupUi(this);
}

ors_qt_2::~ors_qt_2()
{
    sub.shutdown();
    delete ui;
}

void ors_qt_2::fetchData(const turtlesim::Pose &msg){
    linVel=msg.linear_velocity;
    angVel=msg.angular_velocity;
    x=msg.x;
    y=msg.y;
    theta=msg.theta;
}

void ors_qt_2::update()
{
    QWidget::update();
    ros::spinOnce();
}

void ors_qt_2::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

     QPolygon poly;

     poly << QPoint(x+ 10*cos(theta),y+10*sin(theta))
          << QPoint(x- 3*sin(theta), y+3*cos(theta))
          << QPoint(x+ 3*sin(theta), y-3*sin(theta))
          << QPoint(x+ 10*cos(theta),y+10*sin(theta));
     //triangle pointing to turtle's direction

     // Brush
     QBrush brush;
     brush.setColor(Qt::green);
     brush.setStyle(Qt::SolidPattern);

     // Fill polygon
     QPainterPath path;
     path.addPolygon(poly);

     // Draw polygon
     painter.drawPolygon(poly);
     painter.fillPath(path, brush);
}
