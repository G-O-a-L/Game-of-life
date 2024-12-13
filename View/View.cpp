#include "View.hpp"

// Constructor implementation for the View class
View::View() {}

// Implementation of the cliMethod to handle command-line interface interactions
void View::cliMethod(FileOut& file_out, GameLogic& gameLogic) {
    // Prompt user to enter the number of iterations
    int t;
    std::cout << "Enter the number of iteration wanted: ";
    std::cin >> t;

    // Validate user input and handle invalid inputs
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> t;
    }

    // Perform game logic iterations and write results to file
    for (auto i = 0; i < t; ++i) {
        gameLogic.nextStep(0);
        file_out.writeResults(gameLogic.getTab());
    }
}

// Implementation of the guiMethod to handle graphical user interface interactions
void View::guiMethod(FileIn& file_in, GameLogic& gameLogic) {
    // Create a GUI object and run it
    GUI gui(file_in.getX(), file_in.getY(), gameLogic);
    gui.run();
}

// Implementation of the run method to start the game
void View::run() {
    // Create FileIn and FileOut objects
    FileIn file_in;
    FileOut file_out;

    // Set filename, content, and fields for the FileIn object
    file_in.setFilename();
    file_in.setContent();
    file_in.setFields();

    // Create a GameLogic object using the FileIn object's data
    GameLogic gameLogic(file_in.getCells(), file_in.getX(), file_in.getY());

    // Prompt user to choose an interface (CLI or GUI)
    size_t interface;
    std::cout << "Which interface do you want to use? (1: CLI | 2: GUI) : " << std::endl;
    std::cin >> interface;

    // Validate user input and handle invalid inputs
    while (std::cin.fail() || interface != 1 && interface != 2) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> interface;
    }

    // Handle user's interface choice
    switch (interface) {
        case 1:
            // Create a new View object and call its cliMethod
            View().cliMethod(file_out, gameLogic);
            break;

        case 2:
            // Create a new View object and call its guiMethod
            View().guiMethod(file_in, gameLogic);
            break;

        default:
            // Handle invalid interface choice
            std::cout << "Invalid choice" << std::endl;
            break;
    }
}

// Implementation of the unitTest method to perform unit tests for the View class
bool View::unitTest() {
    // Define a test grid for the unit test
    std::vector<int> grid = {
        {0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0}
    };

    // Create a GameLogic object using the test grid
    GameLogic gameLogic(grid, 5, 5);

    // Get the initial game state
    std::vector<std::vector<Cell>> test_grid = gameLogic.getTab();

    // Perform a game logic iteration
    gameLogic.nextStep(0);

    // Print the initial game state
    std::cout << "Unit test grid: " << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << std::to_string(test_grid[i][j].getState()) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;

    // Print the game state after the iteration
    std::cout << "Unit test results: " << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << gameLogic.getTab()[i][j].getState() << " ";
        }
        std::cout << std::endl;
    }

    // Define the expected game state after the iteration
    std::vector<std::vector<Cell>> exp_grid = {
        {Cell(0), Cell(0), Cell(0), Cell(0), Cell(0)},
        {Cell(0), Cell(0), Cell(0), Cell(0), Cell(0)},
        {Cell(0), Cell(1), Cell(1), Cell(1), Cell(0)},
        {Cell(0), Cell(0), Cell(0), Cell(0), Cell(0)},
        {Cell(0), Cell(0), Cell(0), Cell(0), Cell(0)}
    };

    // Compare the actual game state with the expected game state
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (exp_grid[i][j].getState() != gameLogic.getTab()[i][j].getState()) {
                return false;
            } else { return true; }
        }
    }
    return false;
}