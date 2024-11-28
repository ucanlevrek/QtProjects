#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentState(Placement) {

    setupBackground();
    setupGrids();

    setupUIElements();
    setupShips();
    initializeUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupBackground(){
    backgroundGIF = new QMovie(":/images/maps/BG.gif");
    bgProcessLabel = new QLabel(this);

    bgProcessLabel->setMovie(backgroundGIF);
    bgProcessLabel->setScaledContents(true);

    backgroundGIF->start();
    //bgProcessLabel->setGeometry(0,0,width(),height());
    bgProcessLabel->lower();
}


void MainWindow::setupUIElements(){
    setFixedSize(900,600);
    bgProcessLabel->setGeometry(0,0,width(),height());
    stateLabel = new QLabel();
    //Create Layouts
    gameLayout = new QGridLayout();
    shipLayout = new QGridLayout();

    playerGrid->layout->setSpacing(0);
    enemyGrid->layout->setSpacing((0));

    //Create Buttons
    startButton = new QPushButton("Start Game");
    restartButton = new QPushButton("Restart");
    randomPlaceButton = new QPushButton("Place Randomly");
}

void MainWindow::setupShips(){

    for(int id = 0; id<5; ++id){
        int size = shipSizes[id];
        QPushButton *shipButton = new QPushButton(QString::number(size));
        shipButton->setFixedSize(size *30,30);
        shipButton->setStyleSheet("background-color:lightgrey;");
        if(id < 3){
            shipLayout->addWidget(shipButton, 0, id);
        }else{
            shipLayout->addWidget(shipButton, 1, id-3);
        }
    }
}


void MainWindow::setupGrids(){
    playerGrid = new Grid();
    enemyGrid = new Grid();
}


void MainWindow::initializeUI(){


    //Add to layouts
    gameLayout->addWidget(stateLabel, 0, 0);
    gameLayout->addWidget(startButton, 1, 0);
    gameLayout->addWidget(restartButton, 1, 1);
    gameLayout->addLayout(playerGrid->layout, 2, 0);
    gameLayout->addLayout(enemyGrid->layout, 2, 1);


    gameLayout->addWidget(randomPlaceButton, 3, 0);
    gameLayout->addLayout(shipLayout, 4, 0);


    gameLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gameLayout->setAlignment(Qt::AlignCenter);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gameLayout);
    setCentralWidget(centralWidget);

}



//Helper functions

void MainWindow::handlePlayerButtonClick(int row, int col){
    /*
    playerButtons[row][col]->setText("X");
    playerButtons[row][col]->setFlat(true);
    playerButtons[row][col]->setIcon(QIcon());
    playerButtons[row][col]->setDisabled(true);
*/
}

void MainWindow::handleEnemyButtonClick(int row, int col){
    /*
    enemyButtons[row][col]->setText("X");
    enemyButtons[row][col]->setFlat(true);
    enemyButtons[row][col]->setIcon(QIcon());
    enemyButtons[row][col]->setDisabled(true);
    */
}


void MainWindow::restartGame(){

}
