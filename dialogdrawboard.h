#ifndef DIALOGDRAWBOARD_H
#define DIALOGDRAWBOARD_H

#include <QDialog>
#include <QPainter>
#include <windows.h>
#include <sys/stat.h>

namespace Ui {
class DialogDrawBoard;
}

class DialogDrawBoard : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDrawBoard(QWidget *parent = nullptr);
    ~DialogDrawBoard();
    void paintEvent(QPaintEvent *event);
    void setBoard(int nn,int** b,int** c,int d);
    void reDraw();

private:
    Ui::DialogDrawBoard *ui;
    int n;
    int delay;
    double scaleRate;
    int** board;
    int** color;
    int L[4][3]={
        195,195,195,
        247,218,55,
        71,183,231,
        114,187,53
    };
};

#endif // DIALOGDRAWBOARD_H
