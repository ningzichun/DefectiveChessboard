#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogdrawboard.h"
#include "chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void finished();


private slots:

private:
    Ui::MainWindow *ui;
    DialogDrawBoard* drawboard;
    ChessBoard* chess;
};
#endif // MAINWINDOW_H
