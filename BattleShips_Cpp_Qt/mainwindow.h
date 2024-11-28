#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include <QMovie>
#include <QLabel>
#include "custombutton.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum GameState{
        Placement,
        Battle
    };

    GameState currentState;

private:
    QLabel *stateLabel;
    // Start-Restart Buttons
    QPushButton *startButton;
    void startGame();

    QPushButton *restartButton;
    void restartGame();

    QPushButton *randomPlaceButton;
    void randomlyPlaceShips();


    QMovie *backgroundGIF;
    QLabel *bgProcessLabel;

    QGridLayout *enemyGridLayout;
    QGridLayout *playerGridLayout;
    QGridLayout *gameLayout;


    //Ship layout to show below player grid before start
    QGridLayout *shipLayout;
    QVector<QPushButton*> shipButtons;
    QVector<int> shipSizes = {2,3,3,4,5};


    //SetupFunctions
    void setupShips();

    void setupUIElements();
    void setupGrids();

    customButton *playerButtons[10][10];
    customButton *enemyButtons[10][10];

    void enterPlacementMode();
    void handlePlacementClick(int row, int col);

    void handleEnemyButtonClick(int row, int col);
    void handlePlayerButtonClick(int row, int col);
    void initializeUI();
    void setupBackground();
    //void initializeGame()
};

#endif // MAINWINDOW_H
