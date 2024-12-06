#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

// Abstract class Button, which cannot be instantiated but serves as a model for different buttons (next and stop)

class Button{
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
  Button(){}

  // Constructor with parameters
  Button(int x, int y, int length, int height): x(x), y(y), length(length), height(height) {}
  
  // Virtual destructor
  virtual ~Button() {}

  // Pure virtual function to handle events
  bool virtual handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

  // Function to draw the button
  void draw(sf::RenderWindow& window){
    window.draw(shape); // Draws the button
  }
};


// Class ButtonNext, inheriting from Button
class ButtonNext : public Button{
public:
  // Default constructor
  ButtonNext() {}

  // Destructor
  ~ButtonNext() {}

  // Constructor with parameter y
  ButtonNext(int y): Button(5,y,40,30){
    // Creates the button shape
    shape.setSize(sf::Vector2f(length,height));

    // Defines the color for the next button
    const sf::Color color_next(19,107,7);

    // Sets the fill color and position of the button
    shape.setFillColor(color_next);
    shape.setPosition(x,y);
  }

  // Function to handle events
  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    
    // Checks if the event is a mouse button press and the left button is pressed
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
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
};


// Class ButtonStop, inheriting from Button
class ButtonStop : public Button{
public:
  // Default constructor
  ButtonStop() {}

  // Destructor
  ~ButtonStop() {}

  // Constructor with parameter y
  ButtonStop(int y): Button(60,y,40,30) { 

    // Creates the button shape
    shape.setSize(sf::Vector2f(length,height));
    // Sets the fill color to red
    shape.setFillColor(sf::Color::Red);
    // Sets the position of the button
    shape.setPosition(x,y);
  }

  // Function to handle events
  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    
    // Checks if the event is a mouse button press and the left button is pressed
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
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
};