#pragma

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "ButtonNext.hpp"
#include "ButtonStop.hpp"
#include "GameLogic.hpp"

// Class representing the Graphical User Interface (GUI) for the Game of Life
class GUI {
private:
    GameLogic& gameLogic; // Reference to the GameLogic object
    int cell_size; // Size of each cell in the grid
    int length; // Number of rows in the grid
    int height; // Number of columns in the grid
    std::vector<int> cellstate; // Vector to store the state of each cell (for testing purposes)
    std::vector<std::vector<int>> grid; // 2D vector to store the grid (for testing purposes)
    sf::RenderWindow window; // SFML window object
    sf::Vector2i mousePosition; // Vector to store the current mouse position

public:
    // Button objects for next and stop actions
    ButtonNext next;
    ButtonStop stop;

    // Constructor for the GUI class
    GUI(int xmax, int ymax, GameLogic& gameLogic);

    // Function to render the window
    void RenderWindow();

    // Function to run the game
    void run();
};