#ifndef GRID_H
#define GRID_H



class Grid
{
public:
    Grid();


    enum State{
        Empty,
        Ship,
        Miss,
        Hit
    };


    void setState(int row, int col, State state);
    State getCellState(int row, int col);
    void initialize();
    void placeShip(int row, int col);
    State cellStates[10][10];

private:

};

#endif // GRID_H
