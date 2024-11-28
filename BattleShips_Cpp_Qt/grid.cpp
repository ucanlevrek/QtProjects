#include "grid.h"
#include <QDebug>

Grid::Grid() {
    initializeGrid();
}



void Grid::initializeGrid(){
    for(int r=0; r<10; ++r){
        for(int c=0; c<10; ++c){
            cells[r][c] = new customButton;
            customButton *cell = cells[r][c];
            cell->setEnabled(false);
        }
    }
}
