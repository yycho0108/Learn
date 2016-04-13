#ifndef ORS_QT_2_H
#define ORS_QT_2_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QPainterPath>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

namespace Ui {
class ors_qt_2;
}

class ors_qt_2 : public QWidget
{
    Q_OBJECT

public:
    explicit ors_qt_2(QWidget *parent = 0);
    //void fetchData(const geometry_msgs::Twist& msg);
    void fetchData(const turtlesim::Pose& msg);
    ~ors_qt_2();
    void update();
    void paintEvent(QPaintEvent *);
private:
    QTimer checkData;
    Ui::ors_qt_2 *ui;
    ros::NodeHandle n;
    ros::Subscriber sub;
    float angVel,linVel;
    float x,y;
    float theta;
};

#endif // ORS_QT_2_H
