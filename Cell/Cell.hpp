#pragma once

class Cell {
private:
    int state;

public:
    Cell() : Cell(0) {}

    Cell(int state) : state(state) {}

    int getState() const { 
        return state; 
    }

    void setState(int new_state) { 
        state = new_state; 
    }
};