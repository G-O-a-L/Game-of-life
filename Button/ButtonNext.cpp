#include "ButtonNext.hpp"

// Default constructor
ButtonNext::ButtonNext() {}

// Constructor with parameter y
ButtonNext::ButtonNext(int y) : Button(5, y, 40, 30) {
    // Creates the button shape
    shape.setSize(sf::Vector2f(length, height));

    // Defines the color for the next button
    const sf::Color color_next(19, 107, 7);

    // Sets the fill color and position of the button
    shape.setFillColor(color_next);
    shape.setPosition(x, y);
}

// Destructor
ButtonNext::~ButtonNext() {}

// Function to handle events
bool ButtonNext::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Checks if the event is a mouse button press and the left button is pressed
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Gets the mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 

        // Checks if the mouse position is within the button area
        if (mousePos.x >= x && mousePos.x <= (x + length) && mousePos.y >= y  && mousePos.y <= (y + height)) {
    
        // Prints a message when the next button is clicked
        std::cout << "Button next clicked" << std::endl;

        // Returns true to indicate the button was clicked
        return true;
        }
    }
    // Returns false if the button was not clicked
    return false;
}