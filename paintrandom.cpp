#include "paintrandom.h"
#include<math.h>
#include<time.h>
#include<QTime>
#include <algorithm>
#include <random> 
#include <iostream> 
void paintrandom::SSleep(int t){
    QEventLoop eventloop;
    QTimer::singleShot(t, &eventloop, SLOT(quit()));
    eventloop.exec();
}
paintrandom::paintrandom(QWidget *parent) : QWidget(parent)
{
    pItem = new QGraphicsSimpleTextItem;
    pScene = new QGraphicsScene(parent);
    pView = new QGraphicsView(pScene, parent);
}


typedef unsigned long long ull;
ull mod=1e9+7;
ull h[100010];
ull prime=233317;

std::random_device rd;
std::mt19937 mt(rd());
int random(int x){
    if (x == 0) return 0;
    mt();
    return mt() % x;
}

int random(int l, int r){
    if (r == 0) return 0;
    mt();
    return mt() % (r-l) + l;
}

QColor yuv2rgb(std::string st){
   int R = random(0,255);
   int G = random(0,255);
   int B = random(0,255);
   double Y = 0.299*R + 0.587*G + 0.114*B;
   while (Y > 100){
       R = random(0,255);
       G = random(0,255);
       B = random(0,255);
       Y = 0.299*R + 0.587*G + 0.114*B;
   }
   return QColor(R, G, B);
}
void paintrandom::hideText(){
    pView->hide();
}
int calc(int base, int y){
    return base + int(0.9* base * (1-(600-y)/600.0));
}
int max1(int a, int b){
    return (a<b)? b:a;
}
int min(int a, int b){
return (a<b)? a:b;
}
void paintrandom::paintStr(QString st, int t, int x, int y){
    bool f = 0;
    if (x != -1 || y != -1) f = 1;
    qDebug()<<st;
    qDebug()<<st.length();
    //QLabel *p = new QLabel(this);
    //p->setText(st);
    //p->show();
    pItem->setText(st);
    //pItem->set
    //int n = st.length();
    QFont font = pItem->font();
    //QFont font = p->font();
    //int base;
    /*if (st == "18年"||st == "19年"||st =="20年"){
           font.setPixelSize(150);
           base = 150;
    }
    else if (st.length()> 20){
            font.setPixelSize(30);
            base = 30;
    }
    else if (st.length()>14){
        font.setPixelSize(40);
        base = 30;
    }
        else{
        font.setPixelSize(50);
            base = 50;
    }  // 像素大小*/
    font.setWeight(QFont::ExtraBold);
    std::string str = st.toStdString();
    //p->setFont(font);
    pItem->setFont(font);
    pScene->addItem(pItem);
    pView->setStyleSheet("background: transparent;border:0px");
    //pView->setAutoFillBackground(true);
    //pScene->setBackgroundBrush(QBrush(QColor(0,0,0,0)));
    //pScene->setStyle( setStyleSheet("padding:0px;border:0px");
    int len = st.length();
    int yScale = min(660, (37-len) * 27);
    if (y == -1) y = random(yScale);
    //int y = 300;
    int wordSum = 36 - yScale/27;
    int wordSize = 1100/wordSum;
    if (st.length() < 11) wordSize =1100/st.length();
    wordSize = wordSize - 0.5*(37-len)/37*wordSize*(1.0-y*1.0/yScale);
    qDebug()<< y <<" "<< wordSum <<" " << wordSize << x;
    int xScale = 1100 - wordSize * len;
    if (x == -1) x = random(max1(40,xScale))+40;
    if (st.length() == 3 && st != "300"){
          yScale = 660- wordSize;
          y = random(yScale);
    }
    qDebug()<< xScale << x;
    font.setPixelSize(wordSize);
   // p->setFont(font);
    //p->adjustSize();
    //p->move(x, y);
    if (st == "fin."){ font.setFamily("Times New Roman"); font.setItalic(true);}
    pItem->setFont(font);
    pView->adjustSize();
    pView->setGeometry(x, y,pView->width(), pView->height());
    //int n1 = random(1, 120, str);
    //if (n1 > 60) n1 = n1 -120;
    //pView->rotate(n1);
    /*pView->adjustSize();
    int hei = pView->height(), wid = pView->width();
    int heimax = 600 - hei, widmax = 930-wid;
    int x = random(widmax, str);
    int y = random(heimax, str);
    int pSize = calc(base, y);
    //if (st.length()>=20) pSize =40;
    font.setPixelSize(pSize);
    pItem->setFont(font);
    pView->adjustSize();
    //heimax = 600 - pView->height();
    //y = random(max1(0, heimax), str);
    //if (pSize == 40) y = 30 + random(40, str);
    x = random(max1(930-pView->width(), 0), str);
    pView->setGeometry(x + 20, y,pView->width(), pView->height());
    */
    //int x2 = random(100, 255);
    //pView->rotate(30);
   // SSleep(100);
    //
    //pView->setStyleSheet("QGraphicsView{color:argb(1,10,10,10);border:argb(0,0,0,0);border-radius:argb(0,0,0,0);background-color:argb(0,0,0,0);}");
    qDebug()<<"ok";
    //int x3= random(0, 100);
    QPalette pa;
    QColor color = yuv2rgb(str);
    pa.setColor(QPalette::WindowText, color);
    //QColor color(random(100, 256, str), random(100, 256, str), random(100, 256, str));
    pItem->setBrush(QBrush(color));
    pView->show();
    color.setAlphaF(0);
    for (int i = 49; i >= 1; i --){
        color.setAlphaF(1-i/50.0);
        //pa.setColor(QPalette::WindowText, color);
        //p->setPalette(pa);
        //p->show();
        pItem->setBrush(QBrush(color));
        pView->show();
        SSleep(t/1.5);
    }
    SSleep(1000);
    if (!f){
    for (int i = 1; i <= 45; i ++){
        color.setAlphaF(1-i/50.0);
        pItem->setBrush(QBrush(color));
        pView->show();
        //color.setAlphaF(1-i/50.0);
        //pa.setColor(QPalette::WindowText, color);
        //p->setPalette(pa);
        SSleep(t);
    }
    }
    return;
}
double max(double a, double b){
    return (a < b)? b: a;
}
void paintrandom::hiding(){
    QBrush q = pItem->brush();
    QColor color = q.color();
    color.setAlphaF(max(color.alphaF() - 0.03, 0));
    pItem->setBrush(QBrush(color));
}
