#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool ABC::test(QString& str)//проверка на мусор
{
    for(int i=0;i<str.size();i++)
    {
        if((str.at(i) < QChar('0'))||(str.at(i) >= QChar('4')))
            return false;
    }
    return true;
}



void ABC::stabil(ABC& a)//выравнимает по длинне строки +1
{
    int s = a.str.size();
    if(s < this->str.size())
        s = this->str.size();

    for(int i = 0; i < s+1; i++)
    {
        if(a.str.size()<s+1)
            a.str.prepend('0');
        if(this->str.size()<s+1)
            this->str.prepend('0');
    }
}

ABC::ABC(QString a)
{
    if(test(a))
        str = a;
    else {
        QMessageBox msg;
        msg.setText(a + "<- неверная строка");
        msg.exec();
    }
}


QString ABC::sum(ABC a)
{
    this->stabil(a);
    bool temp = false;
    int s = this->str.size();
    int ir[s];
    for(int i = s-1; i >= 0; i--)
    {
        if(temp)
        {
            //следит на переносов в слебующий разряд
            ir[i] = 1;
            temp = false;
        }else ir[i] = 0;
        ir[i] += this->str.at(i).digitValue();//приобразуем эдементы Char в int для подсчёта
        ir[i] += a.str.at(i).digitValue();
        if(ir[i] >= 4)
        {
            //следит на переносов в слебующий разряд
            ir[i] -= 4;
            temp = true;
        }
    }
    QString *result = new QString;
    for(int i = 0; i < s; i++)
    {
        result->append(QChar(ir[i]+48));//int to char
    }
    return *result;
}



QString ABC::difference(ABC a)
{
    bool sign = false;
    this->stabil(a);
    bool temp = false;
    int s = this->str.size();
    int ir[s];
    for(int i = s-1; i >= 0; i--)
    {
        if(temp)
        {
            //следит на переносов в слебующий разряд
            ir[i] = -1;
            temp = false;
        }else ir[i] = 0;
        if(this->str >= a.str)//отрецательный ответ
        {
            ir[i] += this->str.at(i).digitValue();//приобразуем эдементы Char в int для подсчёта
            ir[i] -= a.str.at(i).digitValue();
            sign = false;
        }else
        {
            ir[i] -= this->str.at(i).digitValue();//приобразуем эдементы Char в int для подсчёта
            ir[i] += a.str.at(i).digitValue();
            sign = true;
        }
        if(ir[i] < 0)
        {
            ir[i] += 4;
            temp = true;
        }
    }
    QString *result = new QString;
    //ставим минус
    if(sign)
        result->append(QChar(45));
    else result->append(QChar(48));
    for(int i = 1; i < s; i++)
    {
        result->append(QChar(ir[i]+48));//int to char
    }
    return *result;
}

int Dec(QString a)//перевод в Dec
{
    bool test;
    int i = a.toInt(&test,4);
    if(!test)
    {
        QMessageBox msg;
        msg.setText("первод в десятичную систему невозможен!!! \nP.S. скорее всего привышен диапазон int (–2,147,483,648 to 2,147,483,647)");
        msg.exec();
    }
    return i;
}

void MainWindow::on_pushButton_clicked()
{
    ABC first(ui->lineEdit->text());
    ABC second(ui->lineEdit_2->text());
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked())
        ui->textBrowser->setText(QString::number(Dec(first.sum(second))));
    else ui->textBrowser->setText(first.sum(second));
}

void MainWindow::on_pushButton_2_clicked()
{
    ABC first(ui->lineEdit->text());
    ABC second(ui->lineEdit_2->text());
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked())
        ui->textBrowser->setText(QString::number(Dec(first.difference(second))));
    else ui->textBrowser->setText(first.difference(second));
}
