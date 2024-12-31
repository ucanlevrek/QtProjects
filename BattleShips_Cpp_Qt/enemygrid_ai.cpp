#include "enemygrid_ai.h"

EnemyGrid_AI::EnemyGrid_AI(QWidget *parent) {
    initializeGrid(parent);
    initializeShips();
}


void EnemyGrid_AI::setCellArt(GridButton *cell){
    cell->hiddenIcon = QIcon(":/images/maps/enemy_hidden.png");
    cell->hiddenIcon.addPixmap(QPixmap(":/images/maps/enemy_hidden.png"), QIcon::Disabled);
    cell->hitIcon= QIcon(":/images/maps/enemy_hit.png");
    cell->hitIcon.addPixmap(QPixmap(":/images/maps/enemy_hit.png"), QIcon::Disabled);
    cell->missIcon = QIcon(":/images/maps/enemy_miss.png");
    cell->missIcon.addPixmap(QPixmap(":/images/maps/enemy_miss.png"), QIcon::Disabled);

}

