#pragma once

#include <vector>

#include "Cell.hpp"

using namespace std;

class Grid {
private:
    // Current grid state
    vector<vector<Cell>> crnt_tab;
    // Next grid state
    vector<vector<Cell>> next_tab;

public:
    // Constructor to initialize the grid with a given state
    Grid(vector<int> tab, int x, int y);

    // Get the current grid state
    vector<vector<Cell>> getTab() const;

    // Set the next grid state
    void setNextTab(vector<vector<Cell>> tab);

    // Update the current grid state with the next state
    void nextToCurrent();

    // Check if the current and next grid states are identical
    bool checkIfSame();

    // Modify the state of a cell at a given position
    void modify(int y, int x);
};