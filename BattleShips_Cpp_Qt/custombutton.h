#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QIcon>

class customButton : public QPushButton {
    Q_OBJECT


public:
    customButton(QWidget *parent= nullptr, bool isPlayer = true);
    enum CellState{
        Hidden,
        Empty,
        Ship,
        Hit,
        Miss
    };
    bool isOccupied;
    void setButtonState(CellState state);
    CellState getButtonState() const;

private:
    CellState currentState;
    void updateAppearance();
    bool isPlayer;
};

#endif // CUSTOMBUTTON_H
