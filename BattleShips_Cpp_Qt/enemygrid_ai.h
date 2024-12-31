#ifndef ENEMYGRID_AI_H
#define ENEMYGRID_AI_H

#include <QObject>
#include <QWidget>
#include "grid.h"

class EnemyGrid_AI : public Grid
{
    Q_OBJECT
public:
    explicit EnemyGrid_AI(QWidget *parent = nullptr);

    void setCellArt(GridButton *cell) override;
};

#endif // ENEMYGRID_AI_H
