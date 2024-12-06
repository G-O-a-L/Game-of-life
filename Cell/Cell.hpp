#pragma once

// Define a class to represent a cell with a state
class Cell {
private:
    // The state of the cell, represented as an integer
    int state;

public:
    // Default constructor, initializes the cell with a state of 0
    Cell() : Cell(0) {}

    // Constructor to initialize the cell with a specific state
    Cell(int state) : state(state) {}

    // Method to retrieve the current state of the cell
    int getState() const { 
        return state; 
    }

    // Method to update the state of the cell
    void setState(int new_state) { 
        state = new_state; 
    }
};