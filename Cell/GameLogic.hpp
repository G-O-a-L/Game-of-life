#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <tbb/tbb.h>
#include "Grid.hpp"

using namespace std;

class GameLogic : public Grid {
public:
    // Constructor for GameLogic class, inherits from Grid class
    GameLogic(vector<int> cells, int x /*x max*/, int y /*y max*/) : Grid(cells, x /*x max*/, y /*y max*/) {}

    // Method to calculate the next step in the game
    void nextStep(const bool mode) {
        // Initialize variables for the next generation
        int xmax /*for x*/, ymax /*for y*/;
        // Get the current state of the grid
        std::vector<std::vector<Cell>> current_tab = getTab(); 
        // Create a copy of the current grid for the next generation
        std::vector<std::vector<Cell>> next_tab = getTab(); 

        // Get the dimensions of the grid
        xmax = current_tab[0].size();
        ymax = current_tab.size();
        // Calculate the next step

        size_t xLeft, xRight, yUp, yDown;

        // Use parallel processing to speed up the calculation
        tbb::parallel_for(size_t(0), current_tab.size(), [&](size_t y) {
            // Iterate over each cell in the grid
            for (size_t(x) = 0; x < xmax; x++) {
                // Check if the cell is not an obstacle
                if (current_tab[y][x].getState() == 1 || current_tab[y][x].getState() == 0) {
                    // Initialize a counter for the number of live neighbors
                    int cpt = 0;
                    // Calculate the indices of the neighboring cells
                    size_t yUp = (y == 0) ? ymax - 1 : y - 1;
                    size_t yDown = (y + 1) % ymax;
                    size_t xLeft = (x == 0) ? xmax - 1 : x - 1;
                    size_t xRight = (x + 1) % xmax;

                    // Check the state of each neighboring cell
                    if (current_tab[yDown][x].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[yUp][x].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[yUp][xLeft].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[y][xLeft].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[yDown][xLeft].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[yUp][xRight].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[y][xRight].getState() == 1) {
                        ++cpt;
                    }
                    if (current_tab[yDown][xRight].getState() == 1) {
                        ++cpt;
                    }

                    // Apply the rules of the game to determine the next state of the cell
                    // If the cell is alive and has 2 or 3 live neighbors, it stays alive
                    if (current_tab[y][x].getState() == 1 && cpt != 2 && cpt != 3) {
                        next_tab[y][x].setState(0);
                    }
                    // If the cell is dead and has 3 live neighbors, it becomes alive
                    else if (current_tab[y][x].getState() == 0 && cpt == 3) {
                        next_tab[y][x].setState(1);
                    }
                }
            }
        });

        // Update the grid with the next generation
        setNextTab(next_tab);

        // Check if the game has reached a stable state
        if (mode == 1) {
            // GUI mode
            if (checkIfSame()) {
                // If the game has reached a stable state, throw an exception
                throw runtime_error("Fin du programme, les deux dernière étapes sont identiques");
            }
        }
        // Update the current state of the grid
        nextToCurrent();
    }
};