#ifndef LETTER_H
#define LETTER_H
#include<QLabel>
#include <QMainWindow>
#include<QRadioButton>
#include<QLineEdit>
#include <QCloseEvent>：
class letter : public QMainWindow
{
    Q_OBJECT
public:
    explicit letter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void painttext(const char FILEPATH[],int t, int t1=0);
    QLabel * text[50][50];
    void que1();
    QRadioButton* bnt1, *bnt2, *bnt3, *bnt4;
    QLineEdit* inp1;
    bool que2();
    bool que3();
    bool que4();
    bool que5();
    bool que6();
    void paintimg(QString FILEPATH, int t);
    void paintlast(QString FILEPATH);
    void paintRandomText(const char FILEPATH[], int x = -1, int y = -1, int t = 0);//文件位置，列坐标，行坐标，停留时间, 如果缺省随机位置，自动停留
    void closeEvent(QCloseEvent *event);
    void textClear();
signals:
    void part2Next();
    void part4Begin();
    void part5Begin();
    void part7Begin();
    void part8Begin();
    void paintRandom(QString st, int t, int x, int y);
    void paintRandom1(QString st);
    void part11Begin();
    void closeMain();

public slots:
};

#endif // LETTER_H
