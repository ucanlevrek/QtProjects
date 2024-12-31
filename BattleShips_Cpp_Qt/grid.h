#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include "gridButton.h"
#include "shipButton.h"
#include <QVector>

class Grid : public QWidget
{   Q_OBJECT

public:
    explicit Grid(QWidget *parent=nullptr);

    GridButton *cells[10][10];
    QGridLayout *layout;
    void clear();


    void hitCell(int row, int col);
    void placeRandomShips();
    void handleClick(GridButton *cell);

    void initializeGrid(QWidget *parent);
    virtual void setCellArt(GridButton *cellButton);

    bool validatePlacement(ShipButton *ship, int row, int col);
    void placeShip(ShipButton *ship, int row, int col);

    void initializeShips();

    void shipDragAndDrop(bool isActive);

    QVector<ShipButton*> ships;

    void adjustGridRotation(ShipButton *ship);

    void updateCellStates();
};

#endif // GRID_H

