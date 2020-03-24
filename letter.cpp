#include "letter.h"
#include"startpushbutton.h"
#include<QPainter>
#include<QLabel>
#include<stdio.h>
#include"diag.h"
#include<windows.h>
#include<QEventLoop>
#include<QTimer>
#include<QThread>
#include<QDebug>
#include<QMessageBox>
#include<QRadioButton>
#include<QLineEdit>
#include<QPainter>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsSimpleTextItem>
#include"diag.h"
#include"paintrandom.h"
#include<QMovie>
#include <QCloseEvent>
letter::letter(QWidget *parent) : QMainWindow(parent)
{
    //配置基础信息
    setFixedSize(1654/1.5, 930/1.3);

    setWindowIcon(QPixmap(":/WindowIcon1.jfif"));
    setWindowTitle("A letter to you");

    For(i, 1, TextN) For(j, 1, TextM) text[i][j] = new QLabel;
    For(i, 1, TextN){
        For(j, 1, TextM){
                QFont font("FangSong", 20, 75);
                text[i][j]->setParent(this);
                text[i][j]->show();
                text[i][j]->setFont(font);
                //if (j > st.length())
                    text[i][j]->setText("");
                //else text[i][j]->setText(st.mid(j - 1, 1));
               // text[i][j]->setStyleSheet("QLabel{color:red;border: 3px solid red;border-radius:8px;background-color:rgb(200,101,102);}");  //设置样式表
                text[i][j]->setAlignment(Qt::AlignHCenter|Qt::AlignRight);//Qt::AlignJustify);
                text[i][j]->adjustSize();//自动调整 大小
                int wid = text[i][j]->width();
                int hei = text[i][j]->height();
                int y = 60 + (i - 1) * hei* HJ;//行
                int x = 60 + (j - 1) * wid * LJ;//列
                text[i][j]->move(x, y);
        }
    }
}

std::string st1[400];
char stChar[200];
int uploadText(FILE* &fp){
    int s = 0;
    while (!feof(fp)){
        if (fscanf(fp, "%s", stChar)){
            s++;
            st1[s] = stChar;
            if (s == TextN) break;
        }
        else return s;
    }
    return s;
}
void sleep(int t){
    QEventLoop eventloop;
    QTimer::singleShot(t, &eventloop, SLOT(quit()));
    eventloop.exec();
}
int Max(int a, int b){
return (a<b) ? b:a;
}
int min1(int a, int b){
    return (a<b) ? a:b;
}
bool isChe(QString tmp){
    if ("a" <= tmp && tmp <="z") return 0;
    if ("A" <= tmp && tmp <="Z") return 0;
    if ("0" <= tmp && tmp <="9") return 0;
    if (tmp =="-") return 0;
    if (tmp =="\\") return 0;
    if (tmp =="/") return 0;
    if (tmp ==".") return 0;
   else return 1;
}
void letter::painttext(const char FILEPATH[], int t, int t1){
    FILE * fp = fopen(FILEPATH, "r");
    if (fp ==NULL){
        qDebug()<<"error!";
        return;
    }
    while (1){
        int s = uploadText(fp);
        if (s == 0) break;
        For(i, 1, TextN) For(j, 1, TextM){text[i][j]->clear();text[i][j]->hide();}
        For(i, 1, s){
            QString str = QString::fromStdString(st1[i]);
            bool isClauseEnd = 1;
            if ((str.length()-1 >=0) && (str[str.length() -1] =="$")){
                    str.remove(str.length()-1 , 1);
                    isClauseEnd = 0;
            }
            int y = 60, x= 60;
            For(j, 0, str.length() - 1){
                if (str[j] == '#')
                    text[i][j+1]->setText(" ");
                else text[i][j + 1]->setText(str.mid(j, 1));
                text[i][j+1]->adjustSize();
                int wid = text[i][j+1]->width();
                int hei = text[i][j+1]->height();

                int y = 60 + (i - 1) * hei* HJ;//行
               //列
                text[i][j+1]->move(x, y);
                QPalette pa;
                pa.setColor(QPalette::WindowText,QColor(0,0,1,0));
                text[i][j+1]->setPalette(pa);
                if (t == 0){
                    //整行显示效果
                }
                else{
                    //打字机效果
                    text[i][j+1]->show();
                    for(int k = 0; k <=260; k +=20){
                        pa.setColor(QPalette::WindowText,QColor(0,0,1,min1(k, 255)));
                        text[i][j+1]->setPalette(pa);
                        sleep(4);
                    }
                    sleep(Max(t- 13*4, 0));
                }
                if (j > 0 && isChe(str.mid(j- 1 , 1)) && (!isChe(str.mid(j, 1)))){
                    x += wid * LJ;
                    qDebug() << j;
                }
                else  x += wid * LJ;
            }
            if (t == 0){//直接整行显示
                For(j, 0, str.length() - 1) text[i][j+1]->show();
                for(int k = 0; k <=260; k +=10){
                    For(j, 0, str.length() - 1){
                        QPalette pa;
                        pa.setColor(QPalette::WindowText,QColor(0,0,1,min1(k, 255)));
                        text[i][j+1]->setPalette(pa);
                    }
                    sleep(15);
                }
            }
            if (isClauseEnd) sleep(t1*str.length());
            if (t == 0 && isClauseEnd) sleep(t1 * 21);
            else if (t ==0) sleep(t1*21/2);
        }
        if (s < TextN) break;
    }
    fclose(fp);
}
void letter::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/backletter5.png");
    //pix.load(":/backletter6.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //QPainter painter1(this);
    //pix.load(":/backletter8.png");
    //spainter1.drawPixmap(0, 0, this->width(), this->height(), pix);
    /*//connect(this, &letter::paintrandom, [=]{
        QPainter painter1(this);
        painter1.translate(81,317);
        QFont font("FangSong", 40, 75);
        QString text="1234567"; //设置显示的文本
        QFontMetrics metrics(font);
        int w=metrics.width(text); //获取显示文本的宽度
        int h=metrics.height(); //获取显示文本的高度
        painter1.setFont(font);
        painter1.setPen(Qt::blue);
        painter1.rotate(23);
        painter1.drawText(0,0 ,text);
        painter1.eraseRect(QRectF(0,0-h,w,h));

        //sleep(3000);
        //delete painter1;

        qDebug()<<"w:"<<w; //一个字符大小为12*24,所以宽度为12*7
        qDebug()<<"h:"<<h; //高度为24
    //});*/


}
void letter::que1(){
    int tmp = QMessageBox::information(NULL, "来自灵魂的拷问1", "是否玩游戏？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (tmp != QMessageBox::Yes){
        while (QMessageBox::information(NULL, "来自灵魂的拷问1", "哼！我生气了！再给你一次选择的机会！玩不玩？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) != QMessageBox::Yes);
    }
}
bool letter::que2(){
    bnt1 = new QRadioButton("3.26", this);
    bnt2 = new QRadioButton("4.26", this);
    bnt3 = new QRadioButton("5.26", this);
    bnt4 = new QRadioButton("6.26", this);
    QFont font("FangSong", 20, 75);
    bnt1->setFont(font);
    bnt2->setFont(font);
    bnt3->setFont(font);
    bnt4->setFont(font);
    bnt1->setStyleSheet("QRadioButton{color:red;border: 3px solid red;border-radius:8px}");
    bnt2->setStyleSheet("QRadioButton{color:red;border: 3px solid red;border-radius:8px}}");
    bnt3->setStyleSheet("QRadioButton{color:green;border: 3px solid green;border-radius:8px}}");
    bnt4->setStyleSheet("QRadioButton{color:red;border: 3px solid red;border-radius:8px}}");
    bnt1->adjustSize();
    bnt2->adjustSize();
    bnt3->adjustSize();
    bnt4->adjustSize();
    int x = 440;
    int y = 700;
    int gox = bnt1->height()*1.1;
    bnt1->move(y, x);
    bnt2->move(y, x+gox);
    bnt3->move(y, x+gox*2);
    bnt4->move(y, x+gox*3);
    bnt1->show();
    bnt2->show();
    bnt3->show();
    bnt4->show();
    connect(bnt1, &QRadioButton::clicked, [=](){
        bnt1->hide();
        bnt2->hide();
        bnt3->hide();
        bnt4->hide();
        painttext("part2wrong.txt", 100);
        sleep(1000);
        emit(part2Next());
        return 1;
    });
    connect(bnt2, &QRadioButton::clicked, [=](){
        bnt1->hide();
        bnt2->hide();
        bnt3->hide();
        bnt4->hide();
        painttext("part2wrong.txt", 100);
        sleep(1000);
        emit(part2Next());
        return 1;
    });
    connect(bnt3, &QRadioButton::clicked, [=](){
        bnt1->hide();
        bnt2->hide();
        bnt3->hide();
        bnt4->hide();
        painttext("part2right.txt", 100);
        sleep(1000);
        emit(part2Next());
        return 1;
    });
    connect(bnt4, &QRadioButton::clicked, [=](){
        bnt1->hide();
        bnt2->hide();
        bnt3->hide();
        bnt4->hide();
        painttext("part2wrong.txt", 100);
        sleep(1000);
        emit(part2Next());
        return 1;
    });
    return 0;
}
bool letter::que3(){
    inp1 = new QLineEdit(this);
    inp1->show();
    int s = 0;
    inp1->setMaxLength(3);
    QFont font("FangSong", 20, 75);
    inp1->setFont(font);
    inp1->adjustSize();
    inp1->setFixedWidth(250);
    int gox = inp1->width(), goy = inp1->height();
    inp1->move(150+ gox, 400+goy);
    connect(inp1, &QLineEdit::textChanged, [=](){
            QString st = inp1->text();
            qDebug()<< st;
            if (st.length() == 3){
                if (st != "PRZ"){
                    QMessageBox::warning(NULL, "错误！","错啦！再想想");
                    inp1->clear();
                    inp1->setPlaceholderText("PRZ");
                }
                else{
                    sleep(600);
                    inp1->hide();
                    painttext("part3queright.txt", 100, 50);
                    sleep(1000);
                    emit(part4Begin());
                    return 0;
                }
            }
    });
    return 1;
}
bool letter::que4(){
    int tmp = QMessageBox::information(NULL, "来自灵魂的拷问4", "告诉我嘛~~我猜的对不对", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (tmp == QMessageBox::Yes){
        painttext("part4queright.txt", 100, 50);
        sleep(1000);
        emit(part5Begin());
        return 0;
    }
    else{
        painttext("part4quewrong.txt", 100, 50);
        sleep(1000);
        emit(part5Begin());
        return 0;
    }
}
bool letter::que5(){
    QMessageBox::warning(NULL, "清理","修复完毕！Bingo",QMessageBox::NoButton);
    sleep(2000);
    return 0;
}
bool letter::que6(){
    int tmp = QMessageBox::information(NULL, "来自灵魂的拷问6", "我有没有给你的生活带来乐趣吗", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (tmp != QMessageBox::Yes){
        int tmp = QMessageBox::information(NULL, "来自灵魂的拷问", "哼！我生气了！再给你一次选择的机会！我有么有给你的生活带来乐趣嘛~", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (tmp != QMessageBox::Yes){
            painttext("part6quewrong.txt", 100, 50);
            sleep(1000);
            emit(part7Begin());
        }
        else{
            painttext("part6queright.txt", 100, 50);
            sleep(1000);
            emit(part7Begin());
        }
    }
    else{
        painttext("part6queright.txt", 100, 50);
        sleep(1000);
        emit(part7Begin());
        return 0;
    }
}
void letter::paintimg(QString FILEPATH, int t){
    QPixmap p = QPixmap(FILEPATH);
    QLabel * img = new QLabel();
    QPixmap p1 = p.scaled(1300,1300,Qt::KeepAspectRatio);
    img->setPixmap(p1);
    img->adjustSize();
    //int x= 100, y = 130;
    //img->move(x, y);
    img->show();
    sleep(t);
    img->hide();
    emit(part8Begin());
    return;
}

void letter::paintRandomText(const char FILEPATH[], int x, int y, int t){
    /*
    QGraphicsSimpleTextItem *pItem = new QGraphicsSimpleTextItem;
    pItem->setText("这是一个QGraphicsS");
    QFont font = pItem->font();
    font.setPixelSize(60);  // 像素大小
    pItem->setFont(font);
    QGraphicsScene* pScene = new QGraphicsScene(this);
    pScene->addItem(pItem);
    QGraphicsView* pView = new QGraphicsView(pScene, this);
    pView->setGeometry(0, 0, pScene->width(), pScene->height()*10);
    pView->rotate(30);
    //pView->rotate(30);
    //border:argb(0,0,0,0);border-radius:argb(0,0,0,0);
    pView->setStyleSheet("QGraphicsView{color:argb(1,10,10,10);background-color:argb(0,0,0,0);}");
    pView->show();
    qDebug()<<"ok";
    sleep(2000);
    QColor color(0, 230, 250);
    for (int i = 1; i <= 10; i ++){
        color.setAlphaF(1-i/10.0);
        pItem->setBrush(QBrush(color));
        pView->show();
        sleep(100);
    }*/
    char stChar[200];
    FILE * fp = fopen(FILEPATH, "r");
    if (fp ==NULL){
        qDebug()<<"error!";
        return;
    }
paintrandom *  p[200];
/*for(int i = 0; i <= 5; i++){
    p[i] = new paintrandom();
}
connect(this, &letter::paintRandom, p[0], &paintrandom::paintStr, Qt::QueuedConnection);
connect(this, &letter::paintRandom1, p[1], &paintrandom::paintStr, Qt::QueuedConnection);
 emit(paintRandom("123"));
qDebug()<<"yes";
 emit(paintRandom1("456"));*/
   int s = 0;
    while (!feof(fp)){
        if (fscanf(fp, "%s", stChar)){
            std::string st1 = stChar;
            QString str = QString::fromStdString(st1);
            s++;
            p[s] = new paintrandom(this);
            //p[s]->paintStr(str, 20);
            connect(this, &letter::paintRandom, p[s], &paintrandom::paintStr);
            emit(paintRandom(str, 20, x, y));
            disconnect(this, &letter::paintRandom, p[s], &paintrandom::paintStr);
            for(int i = 1; i <= s-1; i++) p[i]->hiding();
            if (s > 5) p[s - 5]->hideText();
        }
        else{
            break;
        }
    }
    sleep(t);
    for(int i = 1; i <= s; i++) p[i]->hideText();
}
void letter::paintlast(QString FILEPATH){
     QMovie *mv = new QMovie(FILEPATH);
     QLabel * lab = new QLabel;
     lab->setFixedSize(1260,860);

     lab->show();
     //mv->stop();
     connect(mv, &QMovie::stateChanged,[=]{
        qDebug()<<"hide";
        //lab->hide();
        //emit(part11Begin());
        return;
     });
     //lab->show();
     lab->setMovie(mv);
     mv->start();//开始播放
     sleep(25000);
     mv->stop();
     lab->hide();
     emit(part11Begin());
     return;
}

void letter::closeEvent(QCloseEvent *event){
    emit(closeMain());
    qDebug()<<"exit!";
}
void letter::textClear(){
     For(i, 1, TextN) For(j, 1, TextM) text[i][j]->hide();
}
