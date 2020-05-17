#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("残缺棋盘问题");
    drawboard=new DialogDrawBoard(this);
    chess=nullptr;
    drawboard->show();
    drawboard->setWindowTitle("棋盘画板");
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(chess!=NULL){
            chess->terminate();
            delete chess;
        }
        int k=ui->inputK->text().toInt();
        int x=ui->inputX->text().toInt();
        int y=ui->inputY->text().toInt();
        int delay=ui->delayTime->text().toInt();
        bool display=ui->checkBox->checkState();
        ui->logText->clear();
        if (k < 1) {
            ui->logText->append("k的值应为正整数");
            return;
        }
        if(k>30){
            ui->logText->append("k的值太大");
            return;
        }
        int n = pow(2, k);
        QString tip="棋盘坐标从 (0,0) 到 (" + QString::number(n - 1) + "," + QString::number(n - 1) + ")";
        ui->logText->append(tip);
        tip="残缺块为 (" + QString::number(x) + "," + QString::number(y) + ")";
        ui->logText->append(tip);
        if (x < 0 || y < 0 || x >= n || y >= n){
            ui->logText->append("输入的残缺块坐标不正确");
            return;
        }
        ui->logText->append("正在初始化...");


        chess=new ChessBoard(n, x, y,display,drawboard,delay);
        chess->start();

        connect(chess,&QThread::finished,[=](){
            ui->logText->append("完成！");
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
