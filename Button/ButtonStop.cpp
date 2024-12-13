#include "ButtonStop.hpp"

// Default constructor
ButtonStop::ButtonStop() {}

// Constructor with parameter y
ButtonStop::ButtonStop(int y) : Button(60, y, 40, 30) { 
    shape.setSize(sf::Vector2f(length, height)); // Creates the button shape
    shape.setFillColor(sf::Color::Red); // Sets the fill color to red
    shape.setPosition(x, y); // Sets the position of the button
}

// Destructor
ButtonStop::~ButtonStop() {}

// Function to handle events
bool ButtonStop::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Checks if the event is a mouse button press and the left button is pressed
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Gets the mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Checks if the mouse position is within the button area
        if (mousePos.x >= x && mousePos.x <= (x + length) && mousePos.y >= y  && mousePos.y <= (y + height)) {
            // Prints a message when the stop button is clicked
            std::cout << "Button stop clicked" << std::endl;
            // Returns true to indicate the button was clicked
            return true;
        }
    }
    // Returns false if the button was not clicked
    return false;
}