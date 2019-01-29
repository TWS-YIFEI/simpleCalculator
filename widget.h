#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //int opertorToInt(QString oper);
    double calTwoNumberFromOperatorsym(double num1,double num2,QString oper);

private:
    Ui::Widget *ui;

    QPixmap pix;

    double number1=0.0;
    double number2=0.0;
    //double lastnumber=0;
    QString operatorsym="+";

    bool pointflag=true;//true代表 此时可以按.
    bool operatorflag=false;//true代表上一个输入是操作符
    bool number1flag=false;//true代表有值了
    bool number2flag=false;//true代表有值了
    bool lastisoper=true;//true代表上一个是操作符或等号，此时再按数字键，应当清空屏幕重新显示。
    bool lastisequal=true;//上一个是等号，再按加减乘除应当无操作。
};

#endif // WIDGET_H
