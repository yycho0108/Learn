#ifndef ORS_QT_H
#define ORS_QT_H

#include <QWidget>

namespace Ui {
class ors_qt;
}

class ors_qt : public QWidget
{
    Q_OBJECT

public:
    explicit ors_qt(QWidget *parent = 0);
    ~ors_qt();

private:
    Ui::ors_qt *ui;
};

#endif // ORS_QT_H
