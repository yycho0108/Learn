#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTextFile();

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Find_clicked()
{
    QString search = ui->Key->text();
    ui->textEdit->find(search,QTextDocument::FindWholeWords);
}

void MainWindow::update(){
    QWidget::update();
}

void MainWindow::loadTextFile()
{
    QFile input(":/input.txt");
    input.open(QIODevice::ReadOnly);
    QTextStream in(&input);
    QString line = in.readAll();
    input.close();

    ui->textEdit->setPlainText(line);
    QTextCursor c = ui->textEdit->textCursor();
    c.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
}
