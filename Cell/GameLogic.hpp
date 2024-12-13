#pragma once

#include <iostream>
#include <vector>
#include <tbb/tbb.h>

#include "Grid.hpp"

using namespace std;

class GameLogic : public Grid {
public:
    // Constructor for GameLogic class, inherits from Grid class
    GameLogic(vector<int> cells, int x, int y);

    // Method to calculate the next step in the game
    void nextStep(const bool mode);
};