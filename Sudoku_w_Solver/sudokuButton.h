#ifndef SUDOKUBUTTON_H
#define SUDOKUBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QVector>

class SudokuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SudokuButton(QWidget *parent = nullptr);


    int enthropy;
    int block;

    QVector<int> possibilities;

    void reset();

    void updateValues();
    void setValue(int val);
    int getValue();
    void removePossibility(int rmv);

    //undo
    void undoSetValue(int val);


private:
    QGridLayout *numberLayout;
    QLabel *numberLabel;
    QVector<QLabel*> labels;
    int value;


signals:
    void valueSet();
    void undoValueSet();

};

#endif // SUDOKUBUTTON_H
