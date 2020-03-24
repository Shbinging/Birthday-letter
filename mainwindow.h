#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "letter.h"
#include<QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//重写背景
    void paintEvent(QPaintEvent*);
    letter * lett = NULL;
    bool f, f1;
    void letterRun();
    QSound* music = NULL;
signals:
  void que2();
public slots:
  void exit();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
