#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUIElements();

}

MainWindow::~MainWindow() {}


void MainWindow::setupUIElements(){
    setFixedSize(600,600);

    grid = new Grid(this);
    gameLayout = new QGridLayout();

    grid->layout->setSpacing(0);

    //buttons

    resetBtn = new QPushButton("Reset", this);
    connect(resetBtn, &QPushButton::clicked, [this]{
        this->grid->resetGrid();
    });

    undoBtn = new QPushButton("Undo", this);
    connect(undoBtn, &QPushButton::clicked, [this]{
        this->grid->undo();
    });

    nextStepBtn = new QPushButton("Next Step", this);
    connect(nextStepBtn, &QPushButton::clicked, [this]{
        this->grid->checkRepeated();
    });

    solveBtn = new QPushButton("Solve", this);
    connect(solveBtn, &QPushButton::clicked, [this]{
        this->grid->startSolve();
    });


    isValidBtn = new QPushButton("isValid", this);
    connect(isValidBtn, &QPushButton::clicked, [this]{
        qDebug() << this->grid->checkGridValidity();
    });

    gameStateLabel = new QLabel("Unsolved!", this);
    connect(grid, &Grid::solved, [this]{
        this->gameStateLabel->setText("!!! Solved !!!");
    });


    gameLayout->addWidget(resetBtn, 0,0);
    gameLayout->addWidget(undoBtn, 0, 1);
    gameLayout->addWidget(solveBtn, 1,0);
    gameLayout->addWidget(nextStepBtn, 1,1);
    gameLayout->addWidget(gameStateLabel, 2, 0);
    gameLayout->addWidget(isValidBtn, 2, 1);


    //Grid
    gameLayout->addWidget(grid);
    gameLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gameLayout->setAlignment(Qt::AlignCenter);



    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gameLayout);
    setCentralWidget(centralWidget);
}
