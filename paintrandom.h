#ifndef PAINTRANDOM_H
#define PAINTRANDOM_H
#include <QWidget>
#include<QPainter>
#include<QLabel>
#include<stdio.h>
#include"diag.h"
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
class paintrandom : public QWidget
{
    Q_OBJECT
public:
    paintrandom(QWidget *parent = nullptr);

    QGraphicsSimpleTextItem *pItem;
    QGraphicsScene* pScene;
    QGraphicsView* pView;
    void hideText();
    void SSleep(int t);
    void hiding();
signals:

public slots:
     void paintStr(QString st, int t, int x = -1, int y = -1);
};

#endif // PAINTRANDOM_H
