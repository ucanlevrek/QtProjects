#include "gridButton.h"

GridButton::GridButton(QWidget *parent) : QPushButton(parent){
    setFixedSize(40,40);
    setStyleSheet("QPushButton {"
                  "margin:2px;"
                  "border:2px;"
                  "}"
                  );
    setButtonState(Hidden);
    isOccupied = false;
    setFocusPolicy(Qt::NoFocus);
}


void GridButton::setButtonState(CellState state){

    currentState = state;
    updateAppearance();
}

GridButton::CellState GridButton::getButtonState() const{
    return currentState;
}

void GridButton::updateAppearance(){
    switch(currentState){
        case Hidden:
            setIcon(hiddenIcon);
            setIconSize(QSize(40,40));
            break;

        case Hit:
            setIcon(hitIcon);
            setIconSize(QSize(40,40));
            setEnabled(false);
            break;

        case Miss:
            setIcon(missIcon);
            setIconSize(QSize(40,40));
            setEnabled(false);
            break;
        };

}
