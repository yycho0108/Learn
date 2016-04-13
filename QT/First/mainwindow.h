#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>\

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadTextFile();

private slots:
    void on_Find_clicked();
private:
    void update();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
