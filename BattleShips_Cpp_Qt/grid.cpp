#include "grid.h"


Grid::Grid() {
    initializeGrid();
}



void Grid::initializeGrid(){
    layout = new QGridLayout();
    for(int r=0; r<10; ++r){
        for(int c=0; c<10; ++c){
            cells[r][c] = new customButton;
            customButton *cell = cells[r][c];
            cell->setEnabled(true);
            cell->setIconSize(QSize(40,40));
            layout->addWidget(cell, r, c);
        }
    }
}
