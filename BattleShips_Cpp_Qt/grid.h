#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QWidget>
#include "custombutton.h"

class Grid
{
public:
    Grid();

    customButton *cells[10][10];

    void clear();
    void enable();
    void disable();

    void hitCell(int row, int col);

    void placeRandomShips();

    void initializeGrid();
};

#endif // GRID_H
