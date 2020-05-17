#include "dialogdrawboard.h"
#include "ui_dialogdrawboard.h"
#include<QDebug>
#include<QTimer>
DialogDrawBoard::DialogDrawBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDrawBoard)
{
    board=nullptr;
    color=nullptr;
    ui->setupUi(this);
}

DialogDrawBoard::~DialogDrawBoard()
{
    delete ui;
}

void DialogDrawBoard::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.translate(5,5);
    painter.scale(scaleRate,scaleRate);
    QPen pen(QColor(100,100,100));

    QFont font = painter.font();
    font.setPixelSize(6);
    painter.setFont(font);
    pen.setWidth(1);
    painter.setPen(pen);
    if(color!=nullptr){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int tmp=color[i][j];
                painter.setBrush(QColor(L[tmp][0], L[tmp][1], L[tmp][2]));
                const QRect rectangle = QRect(i*10, j*10, 10, 10);
                painter.drawRect(rectangle);
                painter.drawText(rectangle, Qt::AlignCenter,QString::number(board[i][j]));
            }
        }
    }

}
void DialogDrawBoard::setBoard(int nn,int** b,int** c,int d){
    ui->label->setText("");
    this->n=nn;
    this->board=b;
    this->color=c;
    this->delay=d;
    int windowSize=this->size().width();
    if(this->size().height()<windowSize)windowSize=this->size().height(); //获取窗口大小
    int boardSize=n*10;
    scaleRate=(windowSize-10)*1.0/boardSize; //计算缩放比例
}
