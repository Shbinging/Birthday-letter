#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include "startpushbutton.h"
#include<QDebug>
#include"letter.h"
#include<QTimer>
#include<QMessageBox>
#include<QEventLoop>
#include<QTimer>
#include<QThread>
#include<QRadioButton>
#include<QDir>
#include<QSoundEffect>
#include<QSound>
void Sleep(int t){
    QEventLoop eventloop;
    QTimer::singleShot(t, &eventloop, SLOT(quit()));
    eventloop.exec();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f = 0;
    this->setAttribute(Qt::WA_DeleteOnClose);
    music = new QSound(":/backmusic.wav", this);
    music->setLoops(QSound::Infinite);

    setFixedSize(481*2, 317*2);

    setWindowTitle("雯玥机器人 Powered by Shbing V1.2");

    setWindowIcon(QPixmap(":/WindowIcon1.jfif"));

    StartPushbutton * startbtn = new StartPushbutton(":/StartIcon.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5, this->height()*0.5- startbtn->height()*0.5 -30);
    //实例化信纸
    lett = new letter;
    f1 = 0;
    //进入信纸
    //hide();
   // lett->show();
    //lett->painttext();
    connect(lett, &letter::closeMain, this, &MainWindow::exit);
    connect(startbtn, &StartPushbutton::clicked, [=](){
           qDebug()<< "start!";
            startbtn->zoom1();
            startbtn->zoom2();

            //延时进入
            QTimer::singleShot(500, this, [=](){
                this->hide();
                //进入信纸
                lett->show();

                letterRun();

            });
   });
}

MainWindow::~MainWindow()
{
    lett->close();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Back1.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

}
void MainWindow::exit(){
    qDebug()<<"exit main";
    f1 = 1;

    this->close();
}
void MainWindow::letterRun(){
    //lett->paintRandomText("PART8.txt");
    //lett->paintlast(":/last1.gif");
    //开场白
   music->play();
   lett->painttext("PART0.txt", 150, 50);
   Sleep(2000);
   lett->painttext("PART1.txt", 150, 50);
    //询问玩不玩
    if (!f1)
       lett->que1();

    //转场
    lett->painttext("loading.txt", 200);
    Sleep(500);

    lett->painttext("PART2.txt", 150, 50);//1

    connect(lett, &letter::part2Next,[=](){//3
            lett->painttext("PART2-3.txt", 200);
            Sleep(1000);
            lett->painttext("PART3.txt", 0, 50);
            lett->painttext("PART3Que.txt", 0, 50);

            connect(lett, &letter::part4Begin,[=](){//5
                    lett->painttext("PART4.txt", 0, 50);
                    lett->painttext("PART4que.txt", 150, 50);
                    connect(lett, &letter::part5Begin, [=](){//7
                           lett->painttext("PART5.txt", 150, 50);
                           lett->que5();//8
                           lett->painttext("PART6.txt", 150, 50);//9
                           connect(lett, &letter::part7Begin, [=]{//10
                                  lett->textClear();
                                  connect(lett, &letter::part8Begin,[=]{//12
                                       lett->painttext("PART6to7.txt", 150, 50);
                                       lett->textClear();
                                       lett->paintRandomText("PART7.txt");
                                       lett->painttext("PART7to8.txt", 150, 50);
                                       lett->textClear();
                                       lett->paintRandomText("PART8.txt");
                                       lett->painttext("PART9.txt", 150, 50);
                                       lett->paintRandomText("PART9num.txt", 400, 400, 2500);//时间 坐标 坐标
                                       lett->painttext("PART10one.txt", 0, 50);//一行
                                       Sleep(1000);
                                       lett->painttext("PART10two.txt", 150, 50);
                                       connect(lett, &letter::part11Begin, [=]{
                                           lett->textClear();
                                           lett->paintRandomText("PART11.txt", 100, 100, 3000);
                                           //Sleep(5000);
                                           lett->paintRandomText("PART12.txt", 60, 300, 3000);
                                           lett->painttext("end.txt", 150, 50);
                                           lett->textClear();
                                           lett->paintRandomText("fin.txt", 400,200, 3000);
                                           lett->close();
                                           this->close();
                                       });
                                      lett->paintlast(":/last1.gif");
                                  });
                                  lett->paintimg(":/lovestar.png",5000);//11
                           });
                           lett->que6();
                    });
                    lett->que4();//6
            });
            lett->que3();//4

     });
     lett->que2();//2

}
