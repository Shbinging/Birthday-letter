#include "startpushbutton.h"
#include<QPropertyAnimation>
StartPushbutton::StartPushbutton(QString normalImg, QString pressImg){
    QPixmap pix;
    normalImgPath = normalImg;
    pressImgPath = pressImg;
    pix.load(normalImg);

    this->setFixedSize(pix.width() *0.8, pix.height()*0.8);

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()*0.8, pix.height()*0.8));
}

void StartPushbutton::zoom1(){

    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //set duration
    animation->setDuration(200);

    //start loaction
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

    //set curve
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //animation act
    animation->start();
}

void StartPushbutton::zoom2(){

    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //set duration
    animation->setDuration(200);

    //start loaction
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //set curve
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //animation act
    animation->start();
}
