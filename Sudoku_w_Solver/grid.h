#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QStack>
#include <QFile>
#include "sudokuButton.h"
class Grid : public QWidget
{
    Q_OBJECT
public:
    explicit Grid(QWidget *parent = nullptr);

    void Initialize();
    void resetGrid();

    enum Phase{
        Preparation,
        Solving
    };

    struct cellValues{
        int values[9][9];
    };

    struct candidate{
        int position[2];
        int value;
    };

    cellValues getCellValues();

    void undo();



    Phase getCurrentPhase();
    void setPhase(Phase p);
    QGridLayout *layout;
    void setGridFromValues(cellValues cv);

    //Btn functions
    void checkRepeated();
    void startSolve();
    bool bruteForceSolve(QVector<candidate> cndts, cellValues initial);

    //Brute force solve functions
    QVector<candidate> findCandidates();
    int getSolvedCount();
    bool checkGridValidity();


private:
    SudokuButton *buttons[9][9];
    Phase currentPhase;


    QString getButtonStyle(int row, int col);
    int getBlock(int row, int col);
    void showPopup(SudokuButton *button);
    void updateCells(int r, int c, SudokuButton *btn);

    QStack<cellValues> undoStack;

    cellValues currentValues;


    void setCellValues();

    void addToUndoStack(cellValues cv);


signals:
    void solved();


};

#endif // GRID_H
