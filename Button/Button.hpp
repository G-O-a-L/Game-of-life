#pragma once

#include <SFML/Graphics.hpp>

// Abstract class Button, which cannot be instantiated but serves as a model for different buttons (next and stop)

class Button {
protected:
    // Stores the graphical representation
    sf::RectangleShape shape;

    // Stores useful button data
    int x = 0;
    int y = 0;
    int length = 0;
    int height = 0;

public:
    // Default constructor
    Button();

    // Constructor with parameters
    Button(int x, int y, int length, int height);

    // Virtual destructor
    virtual ~Button();

    // Pure virtual function to handle events
    bool virtual handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

    // Function to draw the button
    void draw(sf::RenderWindow& window);
};