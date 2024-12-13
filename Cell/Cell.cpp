#include "Cell.hpp"

// Default constructor, initializes the cell with a state of 0
Cell::Cell() : Cell(0) {}

// Constructor to initialize the cell with a specific state
Cell::Cell(int state) : state(state) {}

// Method to retrieve the current state of the cell
int Cell::getState() const { return state; }

// Method to update the state of the cell
void Cell::setState(int new_state) { state = new_state; }