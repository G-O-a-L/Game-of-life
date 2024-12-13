#include "Button.hpp"
 
// Default constructor
Button::Button() {}

// Constructor with parameters
Button::Button(int x, int y, int length, int height) : x(x), y(y), length(length), height(height) {}

// Virtual destructor
Button::~Button() {}

// Function to draw the button
void Button::draw(sf::RenderWindow& window) { window.draw(shape); } // Draws the button