#include "chessboard.h"
#include <windows.h>
#include <sys/stat.h>
#include <mainwindow.h>

ChessBoard::ChessBoard(int n, int targetX, int targetY,int display,DialogDrawBoard* drawboard,int delay) :n(n),display(display),drawboard(drawboard),delay(delay) { //传入数量的构造函数
    board = new int* [n]; //棋盘
    color = new int* [n]; //颜色
    for (int i = 0; i < n; i++) { //新建二维数组并置零
        board[i] = new int[n] { 0 };
        color[i] = new int[n] { 0 };
    }
    a=targetX;
    b=targetY;
    drawboard->update();

}
ChessBoard::~ChessBoard() { //析构函数
    for (int i = 0; i < n; i++) {
        delete[] board[i]; //棋盘
        delete[] color[i]; //颜色
    }
}
void ChessBoard::run(){
    boardTag = 1; //标记位，表示块的序号
    drawboard->setBoard(n,board,color,delay);
    mark(a, b, 0, 0, n, n, boardTag, 1); //初始化标记
    color[a][b] = 0; //为残缺块填充黑色
}
void ChessBoard::mark(int targetX, int targetY, int startX, int startY, int endX, int endY, int& boardTag, int colorTag) { //参数： 残缺块坐标(targetX,targetY) | 本次递归范围(startX,endX)-(startY,endY) | 块序号标记boardTag | 填充颜色标记colorTag
    int width = endX - startX; //获取本次处理坐标的范围
    if (width <= 2) { //到达递归终点，标记块
        if (!(startX == targetX && startY == targetY)) { board[startX][startY] = boardTag; color[startX][startY] = colorTag; } //为不是残缺块的格子打上三格板序号，打上当前颜色
        if (!(startX == targetX && startY + 1 == targetY)) { board[startX][startY + 1] = boardTag; color[startX][startY + 1] = colorTag; }
        if (!(startX + 1 == targetX && startY == targetY)) { board[startX + 1][startY] = boardTag; color[startX + 1][startY] = colorTag; }
        if (!(startX + 1 == targetX && startY + 1 == targetY)) { board[startX + 1][startY + 1] = boardTag; color[startX + 1][startY + 1] = colorTag; }
        boardTag++; //三格板序号+1
        if(display){
            drawboard->update();
            if(delay){
                Sleep(delay);
            }
        }
        return;
    }
    int middleX = (startX + endX + 1) / 2; //计算中点坐标
    int middleY = (startY + endY + 1) / 2;
    int part = 0; //分四块子棋盘，标号为1-4，递归处理子棋盘
    if (targetX < middleX && targetY < middleY) part = 1; //残缺块在标号为 1 的子棋盘中
    else if (targetX >= middleX && targetY < middleY) part = 2; //残缺块在标号为 2 的子棋盘中
    else if (targetX >= middleX && targetY >= middleY) part = 3; //残缺块在标号为 3 的子棋盘中
    else if (targetX < middleX && targetY >= middleY) part = 4; //残缺块在标号为 4 的子棋盘中
    if (part == 1) mark(targetX, targetY, startX, startY, middleX, middleY, boardTag, 1); //残缺块在标号为 1 的子棋盘中，递归传入的残缺块坐标为 (targetX, targetY)
    else mark(middleX - 1, middleY - 1, startX, startY, middleX, middleY, boardTag, 1); //残缺块不在标号为 1 的子棋盘中，递归传入的残缺块坐标为 (middleX - 1, middleY - 1)
    if (part == 2) mark(targetX, targetY, middleX, startY, endX, middleY, boardTag, 2); //残缺块在标号为 2 的子棋盘中，递归传入的残缺块坐标为 (targetX, targetY)
    else mark(middleX, middleY - 1, middleX, startY, endX, middleY, boardTag, 2); //残缺块不在标号为 2 的子棋盘中，递归传入的残缺块坐标为 (middleX, middleY - 1)
    if (part == 3) mark(targetX, targetY, middleX, middleY, endX, endY, boardTag, 1); //残缺块在标号为 3 的子棋盘中，递归传入的残缺块坐标为 (targetX, targetY)
    else mark(middleX, middleY, middleX, middleY, endX, endY, boardTag, 1); //残缺块不在标号为 3 的子棋盘中，递归传入的残缺块坐标为 (middleX, middleY)
    if (part == 4) mark(targetX, targetY, startX, middleY, middleX, endY, boardTag, 2); //残缺块在标号为 4 的子棋盘中，递归传入的残缺块坐标为 (targetX, targetY)
    else mark(middleX - 1, middleY, startX, middleY, middleX, endY, boardTag, 2); //残缺块不在标号为 4 的子棋盘中，递归传入的残缺块坐标为 (middleX - 1, middleY)
    if (part != 1) { board[middleX - 1][middleY - 1] = boardTag; color[middleX - 1][middleY - 1] = 3; } //每个子棋盘取出最靠近中点的一块
    if (part != 2) { board[middleX][middleY - 1] = boardTag; color[middleX][middleY - 1] = 3; } //拼凑出的空间刚好能用一个三格板进行覆盖
    if (part != 3) { board[middleX][middleY] = boardTag; color[middleX][middleY] = 3; }//为在本棋盘中增加的三格板打上标记和颜色
    if (part != 4) { board[middleX - 1][middleY] = boardTag; color[middleX - 1][middleY] = 3; }
    boardTag++;
    if(display){
        drawboard->update();
        if(delay){
            Sleep(delay);
        }
    }
}
