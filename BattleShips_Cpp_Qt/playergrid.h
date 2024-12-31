#ifndef PLAYERGRID_H
#define PLAYERGRID_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "grid.h"

class PlayerGrid : public Grid
{
    Q_OBJECT
public:
    explicit PlayerGrid(QWidget *parent = nullptr);

    void setCellArt(GridButton *cell) override;


};

#endif // PLAYERGRID_H
