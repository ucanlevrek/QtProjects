#include "grid.h"

Grid::Grid(QWidget *parent)
    : QWidget{parent}
{
    layout = new QGridLayout(this);

    setFixedSize(450,450);
    Initialize();



    //TEST!!!!

    /*

    cellValues initCells;

    QFile file(":/testData/rsrcs/newCSV.csv");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in(&file);
    QVector < QVector < int > > b;
    while(!in.atEnd()){
        QString line = in.readLine();
        //qDebug()<<line;
        QStringList nlist = line.split(",");
        QVector<int> intList;
        for(int i=0 ; i<nlist.length() ; ++i){
            intList.append(nlist[i].toInt());
        }
        b.append(intList);
    }

    while(b.length() > 9){
        b.removeLast();
    }

    for(int r=0 ; r<9 ; ++r){
        for(int c=0 ; c<9 ; ++c){
            int nval = b[r][c];
                initCells.values[r][c] = nval;
        }
    }
    setGridFromValues(initCells);
    setCellValues();

    //--------------

    */
}


void Grid::Initialize(){


    for(int r = 0; r < 9; ++r){
        for(int c = 0; c < 9; ++c){
            buttons[r][c] = new SudokuButton;
            SudokuButton *btn = buttons[r][c];
            btn->setStyleSheet(getButtonStyle(r,c));
            int nBlock = getBlock(r,c);
            btn->block = nBlock;

            layout->addWidget(btn, r, c);

            connect(btn, &QPushButton::clicked, [this, btn]{
                showPopup(btn);
            });

            connect(btn, &SudokuButton::valueSet, [this, btn, r, c]{
                updateCells(r,c,btn);
                setCellValues();

            });

            connect(btn, &SudokuButton::undoValueSet, [this, btn, r, c]{
                updateCells(r,c,btn);
                setCellValues();

            });


        }
    }
}

void Grid::setCellValues(){
    for(int r=0; r<9; ++r){
        for(int c=0 ; c<9 ; ++c){
            currentValues.values[r][c] = buttons[r][c]->getValue();
        }
    }
}


void Grid::addToUndoStack(cellValues cv){
    undoStack.push(cv);

}


Grid::cellValues Grid::getCellValues(){
    return currentValues;
}

void Grid::undo(){
    if(!undoStack.isEmpty()){
        cellValues temp = undoStack.pop();
        setGridFromValues(temp);

    }else{
        qDebug() << "Undo history is empty";
    }
}


void Grid::updateCells(int r, int c, SudokuButton *btn){

    int val = btn->getValue();

    for(int i=0 ; i<9 ; ++i){
        if(i != c){
            if(buttons[r][i]->enthropy != 1){
                buttons[r][i]->removePossibility(val);

            }
        }
        if(i != r){
            if(buttons[i][c]->enthropy != 1){
                buttons[i][c]->removePossibility(val);

            }
        }
    }

    int r0 = r%3;
    int c0 = c%3;
    int r1,r2,c1,c2;
    switch(r0){
    case 0:
        r1 = r+1;
        r2 = r+2;
        break;
    case 1:
        r1 = r-1;
        r2 = r+1;
        break;
    case 2:
        r1 = r-1;
        r2 = r-2;
        break;
    }

    switch(c0){
    case 0:
        c1 = c+1;
        c2 = c+2;
        break;
    case 1:
        c1 = c-1;
        c2 = c+1;
        break;
    case 2:
        c1 = c-1;
        c2 = c-2;
        break;
    }

    buttons[r1][c1]->removePossibility(val);
    buttons[r1][c2]->removePossibility(val);
    buttons[r2][c1]->removePossibility(val);
    buttons[r2][c2]->removePossibility(val);



}

int Grid::getBlock(int row, int col){
    int r1 = floor(row/3);
    int c1 = floor(col/3);

    int val = c1 + (r1*3);

    return val;
}

QString Grid::getButtonStyle(int row, int col){
    QString style = "border:2px solid gray;";

    if(row % 3 == 0 && row!=0){
        style+= "border-top: 4px solid black;";
    }
    if(col % 3 == 0 && col != 0){
        style += "border-left:4px solid black;";
    }

    return style;
}




void Grid::showPopup(SudokuButton *button){
    QMenu *popupMenu = new QMenu(this);

    int len = button->possibilities.size();
    int val;
    for(int i = 0 ; i < len ; ++i){
        val = button->possibilities[i];
        QAction *action = new QAction(QString::number(val), popupMenu);
        popupMenu->addAction(action);

        connect(action, &QAction::triggered, [button, val,this]{
            addToUndoStack(currentValues);
            button->setValue(val);
        });
    }


    QPoint globalPos = button->mapToGlobal(QPoint(0,0));
    popupMenu->exec(globalPos);

}

void Grid::setGridFromValues(cellValues cv){
    resetGrid();
    for(int r=0 ; r<9 ; ++r){
        for(int c=0 ; c<9 ; ++c){
            int tempVal = cv.values[r][c];
            if(tempVal != 0){
                buttons[r][c]->undoSetValue(tempVal);
            }
        }
    }
}
void Grid::resetGrid(){
    for(int r=0 ; r<9 ; ++r){
        for(int c=0 ; c<9 ; ++c){
            buttons[r][c]->reset();
        }
    }
}


void Grid::checkRepeated(){
    for(int i=1 ; i<10 ; ++i){
        //rowcheck
        for(int r = 0 ; r<9 ; ++r){
            int valCt = -1;
            for(int c=0 ; c<9 ; ++c){
                QVector<int> possibs = buttons[r][c]->possibilities;
                if(possibs.contains(i)){
                    if(valCt==-1){
                        valCt=c;
                    }else{
                        valCt=-1;
                        break;
                    }
                }
            }

            if(valCt != -1){
                buttons[r][valCt]->setValue(i);
            }
        }

        //column check
        for(int c=0 ; c<9 ; ++c){
            int valCt = -1;
            for(int r=0 ; r<9; ++r){
                QVector<int> possibs = buttons[r][c]->possibilities;
                if(possibs.contains(i)){
                    if(valCt==-1){
                        valCt = r;
                    }else{
                        valCt=-1;
                        break;
                    }
                }
            }

            if(valCt != -1){
                buttons[valCt][c]->setValue(i);
            }

        }

        //blockCheck
        int a = 0;
        while (a<9){
            int b = 0;
            while(b<9){
                int valCt[2] = {-1,-1};
                for(int x = b ; x<b+3 ; ++x){
                    bool foundTwice = false;
                    for(int y = a ; y<a+3 ; ++y){
                        QVector<int> possibs = buttons[x][y]->possibilities;
                        if(possibs.contains(i)){
                            if(valCt[0]==-1){
                                valCt[0] = x;
                                valCt[1] = y;
                            }else{
                                foundTwice = true;
                                break;
                            }
                        }
                    }
                    if(foundTwice){
                        valCt[0] = -1;
                        valCt[1] = -1;
                        break;
                    }
                }
                b+=3;
                if(valCt[0] != -1){
                    buttons[valCt[0]][valCt[1]]->setValue(i);
                }

            }
            a+=3;
        }
    }


}

void Grid::startSolve(){

    cellValues initialValues = getCellValues();
    QVector<candidate> candidates = findCandidates();

    bruteForceSolve(candidates, initialValues);


}

bool Grid::bruteForceSolve(QVector<candidate> cndts, cellValues initial){

    cellValues testValues = getCellValues();

    int cndtCt = cndts.length();
    for(int i = 0; i<cndtCt ; ++i){
        candidate cndt = cndts[i];
        int posx = cndt.position[0];
        int posy = cndt.position[1];

        buttons[posx][posy]->setValue(cndt.value);

        //check repeated untill it doesn't work anymore
        bool noRepeats = false;
        while(!noRepeats){
            cellValues beforeCheck = getCellValues();
            checkRepeated();
            cellValues afterCheck = getCellValues();

            int ct = 0;
            for(int a=0 ; a<9 ; ++a){
                for(int b=0 ; b<9 ; ++b){
                    if(beforeCheck.values[a][b] == afterCheck.values[a][b]){
                        ct++;
                    }
                }
            }
            if(ct == 81){
                noRepeats = true;
            }
        }
        qDebug() << posx << posy << cndt.value;


        //if already solved
        int solvedCells = getSolvedCount();
        bool isValid = checkGridValidity();

        //eveything is okay after hit
        if(solvedCells == 81 && isValid){
            qDebug() <<"solved";
            emit solved();
            return true;
        }

        //wrong solve
        if(!isValid){
            setGridFromValues(initial);
            if(i == cndtCt-1){
                return false;
            }else{
                continue;
            }
        }

        //not everything is solved but grid is going valid
        if(solvedCells != 81 && isValid){
            qDebug() << "brute solve";
            bruteForceSolve(findCandidates(), testValues);
        }


    }

    return false;
}



QVector<Grid::candidate> Grid::findCandidates(){
    QVector<candidate> candidates;
    for(int r=0 ; r<9 ; ++r){
        for(int c=0 ; c<9 ; ++c){
            if(buttons[r][c]->enthropy >1){
                QVector<int> possibs = buttons[r][c]->possibilities;
                for(int possib : possibs){
                    candidate cndt;
                    cndt.position[0] = r;
                    cndt.position[1] = c;
                    cndt.value = possib;
                    candidates.append(cndt);
                }
            }
        }
    }
    return candidates;
}

int Grid::getSolvedCount(){
    //if already solved
    int solvedCells = 0;
    for(int r=0 ; r<9 ; ++r){
        for(int c=0 ; c<9 ; ++c){
            int val = currentValues.values[r][c];
            if(val != 0){
                solvedCells++;
            }
        }
    }

    return solvedCells;
}


bool Grid::checkGridValidity(){
    //rowCheck
    for(int r=0 ; r<9 ; ++r){
        QVector<int>values;
        values.clear();
        for(int c=0 ; c<9 ; ++c){
            int ent = buttons[r][c]->enthropy;
            if(ent == 1){
                int cellVal = buttons[r][c]->getValue();
                if(values.contains(cellVal) == false){
                    values.append(cellVal);
                }else{
                    return false;
                }
            }
        }
    }

    //column check
    for(int c=0 ; c<9 ; ++c){
        QVector<int>values;
        values.clear();
        for(int r=0 ; r<9 ; ++r){
            int ent = buttons[r][c]->enthropy;
            if(ent == 1){
                int cellVal = buttons[r][c]->getValue();
                if(values.contains(cellVal)==false){
                    values.append(cellVal);
                }else{
                    return false;
                }
            }
        }
    }

    //block check

    int a = 0;
    while (a<9){
        int b = 0;
        while(b<9){
            QVector<int> values;
            values.clear();

            for(int x = b ; x<b+3 ; ++x){
                for(int y = a ; y<a+3 ; ++y){
                    int ent = buttons[x][y]->enthropy;
                    if(ent == 1){
                        int cellVal = buttons[x][y]->getValue();
                        if(values.contains(cellVal)==false){
                            values.append(cellVal);
                        }else{
                            return false;
                        }
                    }

                }
            }
            b+=3;
        }
        a+=3;
    }

    return true;

}
