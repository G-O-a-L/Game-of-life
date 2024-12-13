#include "Grid.hpp"

using namespace std;

// Constructor to initialize the grid with a given state
Grid::Grid(vector<int> tab, int x, int y) {
    // Resize the grids to match the given dimensions
    crnt_tab.resize(y, std::vector<Cell>(x));
    next_tab.resize(y, std::vector<Cell>(x));

    // Fill the current grid with the given state
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            crnt_tab[i][j] = Cell(tab[i * x + j]);
        }
    }
}

// Get the current grid state
vector<vector<Cell>> Grid::getTab() const {
    // Return the current grid state
    return crnt_tab;
}

// Set the next grid state
void Grid::setNextTab(vector<vector<Cell>> tab) {
    // Update the next grid state
    next_tab = tab;
}

// Update the current grid state with the next state
void Grid::nextToCurrent() {
    // Copy the next grid state to the current grid state
    crnt_tab = next_tab;
}

// Check if the current and next grid states are identical
bool Grid::checkIfSame() {
    // Iterate through the grid cells and compare their states
    for(int i = 0; i < size(crnt_tab); i++){
        for(int j = 0; j < size(crnt_tab); j++){
            if(crnt_tab[i][j].getState() != next_tab[i][j].getState()){
                // If any cell states differ, return false
                return false;
            }
        }
    }
    // If all cell states match, return true
    return true;
}

// Modify the state of a cell at a given position
void Grid::modify(int y, int x) {
    // Update the cell state by incrementing it modulo 3 (dead -> alive -> obstacle -> dead)
    crnt_tab[y][x].setState(int(crnt_tab[y][x].getState() + 1) % 3);
}