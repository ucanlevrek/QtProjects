#include "grid.h"


Grid::Grid(QWidget *parent) {

}



void Grid::initializeGrid(QWidget *parent){
    layout = new QGridLayout();
    for(int r=0; r<10; ++r){
        for(int c=0; c<10; ++c){
            cells[r][c] = new GridButton(parent);
            GridButton *cell = cells[r][c];
            cell->setEnabled(true);
            setCellArt(cell);
            cell->setIconSize(QSize(40,40));
            cell->setButtonState(GridButton::Hidden);

            layout->addWidget(cell, r, c);
        }
    }
}

void Grid::initializeShips(){
    int shipSizes[5] = {2,3,3,4,5};
    for(int i = 0; i<5 ; ++i){
        int size = shipSizes[i];
        ShipButton *s = new ShipButton(size, this);
        s->isHorizontal = true;
        layout->addWidget(s, i, 0, 1, shipSizes[i]);
        placeShip(s, i, 0);


        s->setFlat(true);
        ships.append(s);

        connect(s, &ShipButton::rotated, this, [this, s]{
            adjustGridRotation(s);
        });

        connect(s, &ShipButton::grabbed, this, [this, s]{

            for(int i = 0; i < this->ships.length(); ++i){
                ShipButton *ship = this->ships[i];
                if(ship->pos() == s->pos()){
                    ships.removeAt(i);
                }
            }
            updateCellStates();
        });

        connect(s, &ShipButton::released, this, [this, s]{
            QPoint shipPos = s->pos() - cells[0][0]->pos();
            int row = shipPos.y()/40;
            int col = shipPos.x()/40;

            row = std::max(0, std::min(row, 9));
            col = std::max(0, std::min(col, 9));

            placeShip(s, row, col);

            ships.append(s);

            updateCellStates();
        });
    }



}

void Grid::setCellArt(GridButton *cell){}

void Grid::handleClick(GridButton *cell){
    bool isHit = cell->isOccupied;
    if (isHit){
        cell->setButtonState(GridButton::Hit);
    }else{
        cell->setButtonState(GridButton::Miss);
    }
}


void Grid::shipDragAndDrop(bool isActive){
    if(isActive){
        //Drag and drop active, placement
        for(ShipButton *sb: ships){
            sb->setAttribute(Qt::WA_TransparentForMouseEvents, false);
            sb->raise();
            setAttribute(Qt::WA_TransparentForMouseEvents, true);
        }

        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j){
                disconnect(cells[i][j], &QPushButton::clicked, nullptr, nullptr);

            }
        }

    }else{
        //Drag and Drop non active, battling
        for(ShipButton *sb: ships){
            sb->setAttribute(Qt::WA_TransparentForMouseEvents, true);
            sb->lower();
        }

        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j){
                connect(cells[i][j], &QPushButton::clicked, [this, i,j]{
                    Grid::handleClick(cells[i][j]);
                });
            }
        }

    }


}

bool Grid::validatePlacement(ShipButton *ship, int row, int col){
    int size = ship->size;
    bool hor = ship->isHorizontal;

    if((hor && col + size > 10) || (!hor && row + size > 10)) return false;

    for(int i = 0; i <size; ++i){
        int r = hor ? row : row+i ;
        int c = hor ? col + i : col;
        if(cells[r][c]->isOccupied == true) return false;
    }
    return true;


}


void Grid::placeShip(ShipButton *ship, int row, int col){
//    int size = ship->size;
    bool hor = ship->isHorizontal;
    bool initialHor = ship->getInitiallyHorizontal();

    if(!validatePlacement(ship, row, col)){
        if(hor == !initialHor){
            ship->toggleOrientation();
        }
        ship->resetPosition();
        return;
    }

    QPoint snapPos = cells[row][col]->pos();
    ship->setPosition(snapPos);
    ship->setInitiallyHorizontal(hor);

}







void Grid::adjustGridRotation(ShipButton *ship){
    int size = ship->size;
    bool hor = ship->isHorizontal;

    QPoint currentPos = ship->pos() - cells[0][0]->pos();
    int row = currentPos.y()/40;
    int col = currentPos.x()/40;

    row = std::max(0, std::min(row, 10-size));
    col = std::max(0, std::min(col, 10-size));

    layout->removeWidget(ship);

    layout->addWidget(ship, row, col, (hor ? 1 : size), (hor ? size: 1));
        qDebug() << "initiated";
}


void Grid::updateCellStates(){
    struct int2{
        int p[2];
    };

    QVector<int2> positions;

    //collect positions
    for(ShipButton *ship: ships){
        bool isHor = ship->isHorizontal;
        int size = ship->size;

        QPoint relPos = ship->pos() - cells[0][0]->pos();
        int firstRow = relPos.y()/40;
        int firstCol = relPos.x()/40;

        for(int i=0; i<size; ++i){
            int2 position;
            int row = isHor ? firstRow : firstRow + i;
            int col = isHor ? firstCol + i : firstCol;

            position.p[0] = row;
            position.p[1] = col;
            positions.append(position);
        }
    }


    //set states of cells
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j <10 ; ++j){
            cells[i][j]->isOccupied = false;
        }
    }

    int posCt = positions.length();
    for(int i = 0; i < posCt; ++i){
        int r = positions[i].p[0];
        int c = positions[i].p[1];

        cells[r][c]->isOccupied = true;
    }
}




