#include "mysetwindow.h"
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <mypushbutton.h>
#include <QTimer>
#include "mainwindow.h"
#include "readywindow.h"
mysetwindow::mysetwindow(QWidget *parent) : QMainWindow(parent)
{
    //配置场景
    this->setFixedSize(1282, 800);
    this->setWindowTitle("游戏设置");
    this->setWindowIcon(QIcon(":/UNO2D/star.png"));

    //设置标题
    QLineEdit *PersonNum = new QLineEdit(this);
    PersonNum->setFont(QFont("微软雅黑", 10, QFont::Bold));
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    PersonNum->setPalette(palette);
    //PersonNum->setPlaceholderText("请输入游戏人数");
    PersonNum->setEchoMode(QLineEdit::Normal);
    PersonNum->setParent(this);
    PersonNum->resize(280, 50);
    //PersonNum->setStyleSheet("padding: -1");
    PersonNum->move(this->width() * 0.5 - 100, this->height() * 0.5 - 20);

    QLineEdit *PersonName = new QLineEdit(this);
    PersonName->setFont(QFont("微软雅黑", 10, QFont::Bold));
    QPalette palettee;
    palettee.setColor(QPalette::Text, Qt::white);
    PersonName->setPalette(palette);
    //PersonName->setPlaceholderText("请输入用户名");
    PersonName->setEchoMode(QLineEdit::Normal);
    PersonName->setParent(this);
    PersonName->resize(280, 50);
    //PersonName->setStyleSheet("padding: -1");
    PersonName->move(this->width() * 0.5 - 100, this->height() * 0.5 + 220);
    PersonName->setStyleSheet("background-color:rgba(0,0,0,0);");
    PersonNum->setStyleSheet("background-color:rgba(0,0,0,0);");
    MyPushButton *yesBtn = new MyPushButton(":/UNO2D/yes.png");
    yesBtn->setParent(this);
    yesBtn->move(this->width() * 0.75, this->height() * 0.65);
    PersonName->show();
    PersonNum->show();
    rdw = new readywindow();

    connect(yesBtn, &MyPushButton::clicked, [=]() {
        //弹起特效
        yesBtn->zoom1();
        yesBtn->zoom2();
        qnum = PersonNum->text();
        qname = PersonName->text();
        rdw->setNumName(qnum, qname);
        QTimer::singleShot(400, this, [=]() {
            //进入设置场景
            qDebug() << qnum;
            qDebug() << qname;
            this->hide();
            rdw->show();
        });
    });

    MyPushButton *gobackBtn = new MyPushButton(":/UNO2D/goback.png");
    gobackBtn->setParent(this);
    gobackBtn->move(this->width() * 0.75, this->height() * 0.75);
    connect(gobackBtn, &MyPushButton::clicked, [=]() {
        //弹起特效
        gobackBtn->zoom1();
        gobackBtn->zoom2();
        QTimer::singleShot(400, this, [=]() {
            //告诉场景返回 主场景监听返回按钮
            emit this->mysetBack();
        });
    });
    connect(rdw, &readywindow::mysetBack, this, [=]() {
        rdw->hide();
        this->show();
    });
}
void mysetwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/UNO2D/back.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    QPixmap pix1;
    pix1.load(":/UNO2D/setup.png");
    painter.drawPixmap(this->width() * 0.37, this->height() * 0.15, pix1.width(), pix1.height(), pix1);
}
