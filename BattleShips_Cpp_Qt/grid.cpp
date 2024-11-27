#include "grid.h"



Grid::Grid() {
    initialize();
}


Grid::State Grid::getCellState(int row, int col){
    return cellStates[row][col];
}

void Grid::initialize(){
    for(int r=0; r<10; ++r){
        for(int c=0; c<10; ++c){
            cellStates[r][c] = Empty;
        }
    }
}
