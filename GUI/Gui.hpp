#pragma once

#include "Button.hpp"
#include "GameLogic.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include<stdexcept>
#include <algorithm>

// Class representing the Graphical User Interface (GUI) for the Game of Life
class GUI{
private:
    // Reference to the GameLogic object
    GameLogic& gameLogic;

    // Size of each cell in the grid
    int cell_size;
    // Number of rows in the grid
    int length;
    // Number of columns in the grid
    int height;

    // SFML window object
    sf::RenderWindow window;
    
    // Vector to store the state of each cell (for testing purposes)
    std::vector<int> cellstate;   
    // 2D vector to store the grid (for testing purposes)
    std::vector<std::vector<int>> grid; 

    // Vector to store the current mouse position
    sf::Vector2i mousePosition; 

public:

    // Button objects for next and stop actions
    ButtonNext next;
    ButtonStop stop;

    // Constructor for the GUI class
    GUI(int xmax, int ymax, GameLogic& gameLogic) : 
        length(xmax),/* Number of rows in the grid */
        height(ymax),/* Number of columns in the grid */
        gameLogic(gameLogic), /* Reference to the GameLogic object */
        cell_size(std::max(5,2000/int(xmax * ymax))), /* Calculate cell size based on grid size */
        window(sf::VideoMode(xmax * cell_size, ymax * cell_size + 50)/* Create window with specified size */, "Game of Life, groupe 4" ) {

        // Initialize next and stop buttons
        next = ButtonNext(height * cell_size + 2/* Calculate button position */);
        stop = ButtonStop(height * cell_size + 2/* Calculate button position */); 
    }


    // Function to render the window
    void RenderWindow() {
        // Clear the window
        window.clear(); 

        // Create rectangle shapes for the bottom stripe and cells
        sf::RectangleShape bottom_stripe(sf::Vector2f(length * cell_size, 50));
        sf::RectangleShape cell(sf::Vector2f(cell_size - 1.0f, cell_size - 1.0f));
        sf::RectangleShape cell_obstacle(sf::Vector2f(cell_size - 1.0f, cell_size - 1.0f));

        // Define colors for the background and obstacles
        static const sf::Color bg(192,192,192);
        static const sf::Color color_obs(65,105,225);

        // Set fill colors for the shapes
        cell.setFillColor(sf::Color::White);
        cell_obstacle.setFillColor(color_obs);
        bottom_stripe.setFillColor(bg);

        // Get the current state of the grid from the GameLogic object
        std::vector<std::vector<Cell>> to_render = gameLogic.getTab(); 

        // Check if the grid is empty
        if (to_render.empty()) {
            // Throw an exception if the grid is empty
            throw std::runtime_error("Invalid array, can't display nothing");
        }

        // Draw each cell in the grid based on its state
        for (int y = 0; y < to_render.size(); y++) { 
            for (int x = 0; x < to_render[0].size(); x++) { 
                // If the cell is alive
                if (to_render[y][x].getState() == 1) {
                    // Set the cell's position and draw it
                    cell.setPosition(x * cell_size, y * cell_size);
                    window.draw(cell);
                }
                // If the cell is an obstacle
                else if (to_render[y][x].getState() != 0 && to_render[y][x].getState() != 1) { 
                    // Set the obstacle's position and draw it
                    cell_obstacle.setPosition(x * cell_size, y * cell_size);
                    window.draw(cell_obstacle);
                }
            }
        }
        // Set the bottom stripe's position and draw it
        bottom_stripe.setPosition(0, cell_size * height);
        window.draw(bottom_stripe); 

        // Draw the next and stop buttons
        next.draw(window); 
        stop.draw(window); 

        // Display the window
        window.display(); 
    }

    // Function to run the game
    void run() {
        // Variable to store the time step
        float temporal_step;
        // Variable to store whether the game is finite or infinite
        bool finite = 1;
        // Prompt the user for the time step
        std::cout << "Pas temporel ? (en ms) : ";
        std::cin >> temporal_step;

        // Create a clock object to track time
        sf::Clock clock; 
    
        // Main game loop
        while (window.isOpen()) {
            // Event object to handle user input
            sf::Event event;
            // Variable to store whether the game is paused
            static bool bstop = 0; 
            // Handle events
            while (window.pollEvent(event)) {
                // If the window is closed, close it
                if (event.type == sf::Event::Closed) window.close();

                // If the stop button is pressed, toggle the pause state
                if (stop.handleEvent(event, window)) { 
                    bstop = !bstop;
                    clock.restart(); 
                }

                // If the game is paused
                if (bstop) { 
                    // If the next button is pressed, advance to the next step
                    if (next.handleEvent(event, window)) {
                        gameLogic.nextStep(finite); 
                        RenderWindow();
                    }

                    // Check if a cell was clicked
                    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                        // Get the current mouse position
                        mousePosition = sf::Mouse::getPosition(window);

                        // If the click was within the grid
                        if (mousePosition.x <= length * cell_size && mousePosition.x > 0 && mousePosition.y <= height * cell_size && mousePosition.y > 0) {
                            // Modify the cell at the clicked position
                            gameLogic.modify(int(mousePosition.y / cell_size),int(mousePosition.x / cell_size));

                            // Render the window
                            RenderWindow();
                        }

                        // Check for secret buttons (easter eggs)
                        if (mousePosition.x <= length * cell_size && mousePosition.x > length * cell_size - 5 && mousePosition.y <= height * cell_size + 50 &&  mousePosition.y >= height * cell_size + 50-5) {
                            // Prompt the user for a new time step
                            std::cout << "Nouvelle intervale de temps voulue : " << std::endl;
                            std::cin >> temporal_step;
                        }
                        if (mousePosition.x <= length * cell_size && mousePosition.x > length * cell_size - 5 && mousePosition.y <= height * cell_size + 50-6 && mousePosition.y >= height * cell_size + 50-11) {
                            // Toggle the finite/infinite state
                            std::cout << "infinite easter egg" << std::endl;
                            finite = !finite;
                        }
                    }
                }
            }

            // If the game is not paused
            if (!bstop) { 
                // Check if the time step has passed
                if (clock.getElapsedTime().asMilliseconds() >= temporal_step) {
                    // Advance to the next step
                    gameLogic.nextStep(finite); 
                    RenderWindow();
                    clock.restart(); 
                }
            }
            // Sleep for 10 milliseconds
            sf::sleep(sf::milliseconds(10));
        }
    }
};