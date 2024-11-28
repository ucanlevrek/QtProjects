#include "custombutton.h"

customButton::customButton(QWidget *parent) : QPushButton(parent){
    setFixedSize(40,40);
    setStyleSheet("margin:2px; border:2px;");
    setButtonState(Empty);
    updateAppearance();
}


void customButton::setButtonState(CellState state){

    currentState = state;
    updateAppearance();
}

customButton::CellState customButton::getButtonState() const{
    return currentState;
}

void customButton::updateAppearance(){
    switch(currentState){
        case Hidden:
            setIcon(QIcon(":/images/maps/enemyButtonIcon.png"));
            setFlat(false);
            break;

        case Empty:
            setIcon(QIcon(":/images/maps/PlayerBorder.png"));
            setFlat(false);
            break;

        case Ship:
            setIcon(QIcon());
            setFlat(false);
            setText("S");
            break;

        case Hit:
            setIcon(QIcon());
            setFlat(true);
            setText("O");
            break;

        case Miss:
            setIcon(QIcon());
            setFlat(true);
            setText("X");
            break;
        };
}
