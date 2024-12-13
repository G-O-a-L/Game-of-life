#pragma

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.hpp"

// Class ButtonStop, inheriting from Button
class ButtonStop : public Button {
public:
    // Default constructor
    ButtonStop();

    // Constructor with parameter y
    ButtonStop(int y);

    // Destructor
    ~ButtonStop();

    // Function to handle events
    bool handleEvent(sf::Event& event, sf::RenderWindow& window) override;
};