#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QPainter pain(this);
//    //pix.load("://Image/jianbian.png");
//    pain.drawPixmap(9999,9999,pix);
//    setMouseTracking(true);

    QPalette p = this->palette();
    p.setColor(QPalette::Window,QColor(Qt::black));
    this->setPalette(p);
    p.setColor(QPalette::Window,QColor(Qt::white));
    ui->labelscreen->setPalette(p);

    //ui->labelscreen->setFrameShape (QFrame::Box);
    ui->labelscreen->setStyleSheet("border-width:2px; border-style:solid; border-color:white;");
    ui->labelscreen->setStyleSheet("color:white");
    ui->labelscreen->setText("0");
    this->setWindowOpacity(0.93);



    QPushButton *qpb[]={ui->pushButton_0,ui->pushButton_1,ui->pushButton_2,
                      ui->pushButton_3,ui->pushButton_4,ui->pushButton_5,
                      ui->pushButton_6,ui->pushButton_7,ui->pushButton_8,
                      ui->pushButton_9,
                      ui->pushButton_neg,ui->pushButton_point,ui->squarebutton,
                      ui->addbutton,ui->subtractbutton,ui->multibutton,ui->divbutton,
                      ui->equalbutton,ui->backbutton,ui->clearbutton};
    for(auto a:qpb){
        connect(a,QPushButton::clicked,this,[=](){
            QString pressbutt=a->text();
            if(pressbutt=="1" || pressbutt=="2" || pressbutt=="3" ||
               pressbutt=="4" || pressbutt=="5" || pressbutt=="6" ||
               pressbutt=="7" || pressbutt=="8" || pressbutt=="9" ){
                if(lastisequal==true){
                    number1flag=false;
                    number2flag=false;
                }
                if(ui->labelscreen->text()=="0"){
                    ui->labelscreen->setText(pressbutt);
                }else if(ui->labelscreen->text().size()<15){
                    if(lastisoper==true){
                        ui->labelscreen->setText("");
                        ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                    }else{
                        ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                    }
                }
                lastisoper=false;
                operatorflag=false;
                lastisequal=false;
            }else if(pressbutt=="0"){
                if(ui->labelscreen->text().size()>=15) return;
                if(ui->labelscreen->text()=="0") return;
                if(lastisoper==true){
                    ui->labelscreen->setText("");
                    ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                }else{
                    ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                }
                lastisoper=false;
                lastisequal=false;
                operatorflag=false;
            }else if(pressbutt=="."){
                if(ui->labelscreen->text().size()>=15) return;
                if(ui->labelscreen->text().size()==1){
                    if(lastisoper==true){
                        ui->labelscreen->setText("0");
                        ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                    }else{
                        ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                    }
                    pointflag=false;
                }else{
                    if(pointflag==true){
                        ui->labelscreen->setText(ui->labelscreen->text()+pressbutt);
                        pointflag=false;
                    }else{
                        return ;
                    }
                }
                lastisequal=false;
                lastisoper=false;
                operatorflag=false;
            }else if(pressbutt=="+" || pressbutt=="-" || pressbutt=="*" || pressbutt=="/"){
                if(operatorflag==true){
                    operatorsym=pressbutt;
                }else{
                    if(number1flag==true&&number2flag==false){
                        //lastnumber=number2;
                        //下面的if没有走，当除数为0时,number2得到的是inf，就直接在屏幕上显示了
                        if(operatorsym=="/"&&number2==0){
                            ui->labelscreen->setText("除数不能为0");
                            emit ui->clearbutton->clicked();
                            return ;
                        }
                        if(lastisequal==true){

                        }else{
                            number2=ui->labelscreen->text().toDouble();
                            number1=calTwoNumberFromOperatorsym(number1,number2,pressbutt);
                            ui->labelscreen->setText(QString::number(number1));
                        }
                    }else if(number1flag==false&&number2flag==false){
                        number1=ui->labelscreen->text().toDouble();
                        number2=number1;
                        ui->labelscreen->setText(QString::number(number1));
                        //lastnumber=number1;
                        number1flag=true;
                    }
                    operatorsym=pressbutt;
                }
                lastisoper=true;
                operatorflag=true;
                lastisequal=false;
            }else if(pressbutt=="="){
                if(number1flag==true&&number2flag==false){
//                    if(operatorflag==true){
//                        //lastnumber=ui->labelscreen->text().toDouble();
//                        //number2=ui->labelscreen->text().toDouble();
//                        number1=calTwoNumberFromOperatorsym(number1,number2,operatorsym);
//                        ui->labelscreen->setText(QString::number(number1));
//                    }else{
//                        //lastnumber=ui->labelscreen->text().toDouble();
//                        number2=ui->labelscreen->text().toDouble();
//                        number1=calTwoNumberFromOperatorsym(number1,number2,operatorsym);
//                        ui->labelscreen->setText(QString::number(number1));
//                    }
                        if(lastisoper==true){

                            number1=calTwoNumberFromOperatorsym(number1,number2,operatorsym);
                            ui->labelscreen->setText(QString::number(number1));
                        }else{
                            number2=ui->labelscreen->text().toDouble();
                            number1=calTwoNumberFromOperatorsym(number1,number2,operatorsym);
                            ui->labelscreen->setText(QString::number(number1));
                        }

                }else if(number1flag==false&&number2flag==false){
                    ui->labelscreen->setText(QString::number(ui->labelscreen->text().toDouble()));
                    number2=ui->labelscreen->text().toDouble();
                }
                lastisequal=true;
                lastisoper=true;
                operatorflag=false;
            }else if(pressbutt=="←"){
                QString qstr=ui->labelscreen->text();
                qstr=qstr.left(qstr.size()-1);
                ui->labelscreen->setText(qstr);
            }else if(pressbutt=="CE"){
                ui->labelscreen->setText("0");
                number1=0.0;
                number2=0.0;
                operatorsym="+";
                //lastnumber=0;

                pointflag=true;//true代表 此时可以按.
                operatorflag=false;//true代表上一个输入是操作符
                number1flag=false;//true代表有值了
                number2flag=false;//true代表有值了
                lastisoper=false;
            }else if(pressbutt=="+/-"){
                number1=ui->labelscreen->text().toDouble();
                number1*=-1;
                ui->labelscreen->setText(QString::number(number1));
                lastisoper=false;
            }else if(pressbutt=="x^2"){
                number1=ui->labelscreen->text().toDouble();
                number1*=number1;
                ui->labelscreen->setText(QString::number(number1));
                lastisoper=false;
            }
        });
    }

    for(auto a: qpb){
        a->setStyleSheet(tr("QPushButton{background-color:#fbf9f9;} QPushButton:hover{background-color:#d0cbcb;} QPushButton:pressed{background-color:#5f5f5f;} "));
    }

}

Widget::~Widget()
{
    delete ui;
}

double Widget::calTwoNumberFromOperatorsym(double num1, double num2, QString oper){
    if(oper=="+"){
        return num1+num2;
    }else if(oper=="-"){
        return num1-num2;
    }else if(oper=="*"){
        return num1*num2;
    }else if(oper=="/"){
        return num1/num2;
    }
    return num1+num2;
}

/*
测试库函数的string to double
QString str="-.999";
double test=str.toDouble();
qDebug()<<test<<endl;
*/

/*
屏幕：默认为0
设置点标志位 true代表 此时可以按.
运算符标志位 true代表上一个输入是操作符
number1flag true代表有值了
number2flag true代表有值了

如果按下：
    1-9
        拿到输入框中的数，
            if为0：
                是：删除0，追加当前数字。
                否：直接追加
            if小于11位
                是：然后后面追加按下的数字。
                否：无操作，不往后追加。
        operatorflag=false
    0
        if 位数>=11 无操作，退出函数
        if 框中位数==1
            if 框中数字==0：
                无操作
            else
                直接追加
        else
            直接追加
        operatorflag=false
    .
        if 框中位数>=11 无操作，退出函数
        if 框中位数==1
            直接追加
            pointflag=false;
        else
            if pointflag==true
                直接追加
                pointflag=false
            else
                无操作，退出函数
        operatorflag=false
    + - *
        if operatorflag==true
            更新运算符
        else
            if num1flag==true&&num2flag==false
                num2=数据框内容(processData)
                num1=num1??num2;  判断除数为0
                num1显示到数据框
            else if num1flag=false&&num2flag==false
                取数据框内容放到num1(processData)
                num1flag=true;
            设置新的运算符
        operatorflag=true
    /

        if operatorflag==true
            更新运算符
        else
            if num1flag==true&&num2flag==false
                num2=数据框内容(processData)
                num1=num1??num2;  判断除数为0
                num1显示到数据框
            else if num1flag=false&&num2flag==false
                取数据框内容放到num1(processData)
                num1flag=true;
            设置新的运算符
        operatorflag=true
    =
        if num1flag==true && num2flag==false
            if operatorflag==true
                num1+=num2;
                num1显示到数据框
            else
                取数据框内容加到num1 processData
                num1显示到数据框
        if num1flag==false && num2flag==false
            取数据框内容处理
            显示到数据框
    ←
        取数据框内容
        删除最后一位
        显示到数据框
    CE
        数据框置0
    +/-
        取数据框内容
        转为double
        * -1
        显示到数据框
    x^2
        取数据框内容
        转为double
        平方
        显示到数据框


注意：
    每次取数据框内容要对数据进行处理(processData)
    可用自带库函数
        去除末尾点
        如果.000 进行取整
        判断是否空
        0.0000转为0


    运算时判断除数为0

测试数据：
    1+2*3*
    1+2*3=

    .+0*
    .+0=

    000+0*
    000+0=

    0*0*
    0*0=

    0/0*
    0/0/
    0/0=

    ===/
*/
