#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include<QThread>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "dialogdrawboard.h"

class ChessBoard :public QThread{ //残缺棋盘类
public:
    ChessBoard(int n, int targetX, int targetY,int display,DialogDrawBoard* drawboard,int delay);
    void run();
    ~ChessBoard();
    void mark(int targetX, int targetY, int startX, int startY, int endX, int endY, int& boardTag, int colorTag);
private:
    int a;
    int b;
    int n; //棋盘宽度
    int boardTag; //三格板标号
    int display; //是否显示处理过程
    int delay;
    int** board; //棋盘
    int** color; //颜色
    DialogDrawBoard* drawboard;
};


#endif // CHESSBOARD_H
