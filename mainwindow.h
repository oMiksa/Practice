#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QtMath>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
class ABC;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

class ABC
{
    //Q_OBJECT
private:
    QString str;
    bool test(QString&);
    void stabil(ABC&);
public:
    ABC(QString);
    QString sum(ABC);
    QString difference(ABC);
    friend int Dec(QString);

};


#endif // MAINWINDOW_H
