#pragma

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.hpp"

// Class ButtonNext, inheriting from Button
class ButtonNext : public Button {
public:
    // Default constructor
    ButtonNext();

    // Constructor with parameter y
    ButtonNext(int y);

    // Destructor
    ~ButtonNext();

    // Function to handle events
    bool handleEvent(sf::Event& event, sf::RenderWindow& window) override;
};