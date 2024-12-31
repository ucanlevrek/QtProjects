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
#include "playergrid.h"
#include "enemygrid_ai.h"
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
    // Start-Restart Buttons

    QPushButton *startButton;
    QPushButton *restartButton;


    QPushButton *randomPlaceButton;
    void randomlyPlaceShips();


    QMovie *backgroundGIF;
    QLabel *bgProcessLabel;


    QGridLayout *gameLayout;

    PlayerGrid *playerGrid;
    EnemyGrid_AI *enemyGrid;



    //SetupFunctions

    void startBattle();
    void startPlacement();

    void setupUIElements();
    void setupGrids();


    void initializeUI();
    void setupBackground();


};

#endif // MAINWINDOW_H
