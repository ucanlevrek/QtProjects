#include "sudokuButton.h"

SudokuButton::SudokuButton(QWidget *parent)
    : QPushButton{parent}
{
    value=0;
    possibilities = {1,2,3,4,5,6,7,8,9};
    enthropy = possibilities.length();

    numberLayout = new QGridLayout(this);
    numberLayout->setSpacing(0);
    numberLayout->setContentsMargins(2,2,2,2);
    updateValues();
    setFixedSize(50,50);
    setEnabled(true);
}

void SudokuButton::reset(){
    value=0;
    possibilities = {1,2,3,4,5,6,7,8,9};
    enthropy = possibilities.length();
    updateValues();

}

void SudokuButton::updateValues(){

    for(QLabel *l: labels){
        delete l;
    }
    labels.clear();

    int len = possibilities.length();
    enthropy = len;

    for(int i = 0; i < len ; ++i){
        int row = floor(i/3);
        int col = i%3;


        numberLabel = new QLabel(QString::number(possibilities[i]));
        numberLabel->setAlignment(Qt::AlignCenter);
        labels.append(numberLabel);

        if(len != 1){
            numberLabel->setStyleSheet("font-size:10px; border:none;");
            numberLayout->addWidget(numberLabel, row,col);
        }else{
            numberLabel->setStyleSheet("font-size:30px; border:none;");
            numberLayout->addWidget(numberLabel,0,0);
        }
    }
}


void SudokuButton::setValue(int val){

    possibilities = {val};
    value = val;
    enthropy = 1;

    updateValues();
    emit valueSet();
}


void SudokuButton::undoSetValue(int val){
    possibilities = {val};
    value = val;
    enthropy = 1;
    updateValues();
    emit undoValueSet();
}

int SudokuButton::getValue(){
    return value;
}

void SudokuButton::removePossibility(int rmv){
    if(enthropy == 1){
        return;
    }

    for(int i=0; i<possibilities.length() ; ++i){
        int *pos = &possibilities[i];
        if( *pos == rmv ){
            possibilities.removeAt(i);
            if(possibilities.length() != 1){
                updateValues();
            }else{
                setValue(possibilities[0]);
            }
        }
    }

}
