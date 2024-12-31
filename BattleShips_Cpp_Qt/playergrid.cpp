#include "playergrid.h"

PlayerGrid::PlayerGrid(QWidget *parent) {
    initializeGrid(parent);
    initializeShips();

}

void PlayerGrid::setCellArt(GridButton *cell){
    cell->hiddenIcon = QIcon(":/images/maps/player_hidden.png");
    cell->hiddenIcon.addPixmap(QPixmap(":/images/maps/player_hidden.png"), QIcon::Disabled);
    cell->hitIcon= QIcon(":/images/maps/player_hit.png");
    cell->hitIcon.addPixmap(QPixmap(":/images/maps/player_hit.png"), QIcon::Disabled);
    cell->missIcon = QIcon(":/images/maps/player_miss.png");
    cell->missIcon.addPixmap(QPixmap(":/images/maps/player_miss.png"), QIcon::Disabled);
}



