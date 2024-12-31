#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QIcon>

class GridButton : public QPushButton {
    Q_OBJECT


public:
    explicit GridButton(QWidget *parent= nullptr);
    enum CellState{
        Hidden,
        Hit,
        Miss
    };
    bool isOccupied;
    void setButtonState(CellState state);
    CellState getButtonState() const;


    QIcon hiddenIcon;
    QIcon hitIcon;
    QIcon missIcon;

private:
    CellState currentState;
    void updateAppearance();
};

#endif // GRIDBUTTON_H
