#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grid.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Grid *grid;

    void setupUIElements();

private:


    QPushButton *undoBtn;
    QPushButton *resetBtn;
    QPushButton *nextStepBtn;
    QPushButton *solveBtn;
    QPushButton *isValidBtn;

    QLabel *gameStateLabel;

    QGridLayout *gameLayout;

};
#endif // MAINWINDOW_H
