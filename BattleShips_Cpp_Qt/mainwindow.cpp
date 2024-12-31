#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentState(Placement) {


    setupBackground();
    setupGrids();

    setupUIElements();
    initializeUI();

    startPlacement();
}

MainWindow::~MainWindow()
{

}


//---------------------------------------------------------//

void MainWindow::setupBackground(){
    backgroundGIF = new QMovie(":/images/maps/BG.gif");
    bgProcessLabel = new QLabel(this);

    bgProcessLabel->setMovie(backgroundGIF);
    bgProcessLabel->setScaledContents(true);

    backgroundGIF->start();
    bgProcessLabel->lower();
}

void MainWindow::setupGrids(){
    playerGrid = new PlayerGrid(this);
    enemyGrid = new EnemyGrid_AI(this);
}



void MainWindow::setupUIElements(){
    setFixedSize(900,600);
    bgProcessLabel->setGeometry(0,0,width(),height());

    //Create Layouts
    gameLayout = new QGridLayout();


    playerGrid->layout->setSpacing(0);
    enemyGrid->layout->setSpacing(0);

    //Create Buttons
    startButton = new QPushButton("Start Game");
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startBattle);
    restartButton = new QPushButton("Restart");
    connect(restartButton, &QPushButton::clicked, this, [=]{
        MainWindow::startPlacement();
    });
    randomPlaceButton = new QPushButton("Place Randomly");

}



void MainWindow::initializeUI(){


    //Add to layouts
    gameLayout->addWidget(startButton, 1, 0);
    gameLayout->addWidget(restartButton, 1, 1);

    gameLayout->addLayout(playerGrid->layout, 2, 0);
    gameLayout->addLayout(enemyGrid->layout, 2, 1);


    gameLayout->addWidget(randomPlaceButton, 3, 0);


    gameLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gameLayout->setAlignment(Qt::AlignCenter);

//    gameLayout->removeWidget(stateLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gameLayout);
    setCentralWidget(centralWidget);


}



//---------------- Button Functions---------------

void MainWindow::startBattle(){

    currentState = Battle;
    playerGrid->shipDragAndDrop(false);
    playerGrid->updateCellStates();



}

void MainWindow::startPlacement(){

    currentState = Placement;
    playerGrid->shipDragAndDrop(true);

}
