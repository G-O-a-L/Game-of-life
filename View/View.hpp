#pragma

#include <iostream>
#include <string>
#include <limits>

#include "FileIn.hpp"
#include "FileOut.hpp"
#include "GameLogic.hpp"
#include "GUI.hpp"

class View {
public:
    View();
    void cliMethod(FileOut& file_out, GameLogic& gameLogic);
    void guiMethod(FileIn& file_in, GameLogic& gameLogic);
    void run();
    bool unitTest();
};

View::View() {}

void View::cliMethod(FileOut& file_out, GameLogic& gameLogic) {
    int t;
    std::cout << "Enter the number of iteration wanted: ";
    std::cin >> t;
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> t;
    }
    for (auto i = 0; i < t; ++i) {
        gameLogic.nextStep(0);
        
        file_out.writeResults(gameLogic.getTab());
    }
}

void View::guiMethod(FileIn& file_in, GameLogic& gameLogic) {
    GUI gui(file_in.getX(), file_in.getY(), gameLogic);
    gui.run();
}

void View::run() {
    FileIn file_in;
    FileOut file_out;
    file_in.setFilename();
    file_in.setContent();
    file_in.setFields();

    GameLogic gameLogic(file_in.getCells(), file_in.getX(), file_in.getY());

    size_t interface;
    std::cout << "Which interface do you want to use? (1: CLI | 2: GUI) : " << std::endl;
    std::cin >> interface;
    while (std::cin.fail() || interface != 1 && interface != 2) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> interface;
    }
    switch (interface) {
        case 1:
            View().cliMethod(file_out, gameLogic);
            break;

        case 2:
            View().guiMethod(file_in, gameLogic);
            break;

        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }
}

bool View::unitTest() {
    // Unit tests for the View class
    vector<vector<Cell>> grid = {
        0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0
    }
    GameLogic gameLogic(grid, 5, 5);

    gameLogic.nextStep(0);

    std::cout << "Unit test grid: " << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << grid[i, j] << " ";
        }
    }
    std::cout << "\n" << std::endl;

    std::cout << "Unit test results: " << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << gameLogic.getCell(i, j).getState() << " ";
        }
    }

    if (gameLogic.getTab() == grid) {
        return true;
    }
}