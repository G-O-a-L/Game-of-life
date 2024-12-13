#pragma

// Include necessary libraries for input/output, string manipulation, and numeric limits
#include <iostream>
#include <string>
#include <limits>

// Include custom header files for file input/output and game logic
#include "FileIn.hpp"
#include "FileOut.hpp"
#include "GameLogic.hpp"
#include "Gui.hpp"

// Define a class View to handle user interface and game logic interactions
class View {
public:
    // Constructor for the View class
    View();

    // Method to handle command-line interface interactions
    void cliMethod(FileOut& file_out, GameLogic& gameLogic);

    // Method to handle graphical user interface interactions
    void guiMethod(FileIn& file_in, GameLogic& gameLogic);

    // Method to run the game
    void run();

    // Method to perform unit tests for the View class
    bool unitTest();
};