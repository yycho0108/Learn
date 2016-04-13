#include "ors_qt.h"
#include "ui_ors_qt.h"
ors_qt::ors_qt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ors_qt)
{
    ui->setupUi(this);
}

ors_qt::~ors_qt()
{
    delete ui;
}
