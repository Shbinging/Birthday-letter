#ifndef STARTPUSHBUTTON_H
#define STARTPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
class StartPushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit StartPushbutton(QWidget *parent = nullptr);

    //构造函数
    StartPushbutton(QString normalImg, QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;
    void zoom1();//向下跳
    void zoom2();//向上跳
signals:

};

#endif // STARTPUSHBUTTON_H
