#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // La classe abstraite button, qui ne peux pas être instantié mais sert de modèle pour les différents boutons (next et stop) //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Button{
protected:
  // Stocke la représentation graphique
  sf::RectangleShape shape;

  //Stocke les données utile du boutton
  int x = 0;

  int y = 0;

  int length = 0;

  int height = 0;

public:
 
 Button(){}

  Button(int x, int y, int length, int height): x(x), y(y), length(length), height(height) {}
  
  virtual ~Button() {}

  bool virtual handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

  void draw(sf::RenderWindow& window){
    window.draw(shape); // Dessine le boutton
  }
};


/************************************************************************************************************/

class ButtonNext : public Button{
public:
  ButtonNext() {}

  ~ButtonNext() {}

  ButtonNext(int y): Button(5,y,40,30){
    // créer la forme du boutton
    shape.setSize(sf::Vector2f(length,height));

    const sf::Color color_next(19,107,7);

    shape.setFillColor(color_next);
    shape.setPosition(x,y);
  }

  // En fonction de la sortie, il y aura un code dans GUI qui sera utilisé pour lancer la prochaine itération

  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
     sf::Vector2i mousePos = sf::Mouse::getPosition(window); // On traque la position de notre sourie
  
     // Regarde si : L'évènement est la pression du bouton de la souris, puis regarde si le boutton pressé est le click gauche, puis regarde si le clique ce trouve bien sur l'emplacement du boutton
    
     if (mousePos.x >= x && mousePos.x <= (x + length) && mousePos.y >= y  && mousePos.y <= (y + height)) {
      
      std::cout << "Button next clicked" << std::endl;

      return true;
     }
    }
    return false;
  }
};

/*********************************************************************************************************/

class ButtonStop : public Button{
public:
  ButtonStop() {}

  ~ButtonStop() {}

  // Paramêtres : y origin | longueur du bouton | largueur du bouton, notre bouton est donc custom
  ButtonStop(int y): Button(60,y,40,30) { // Le y est toujours le même

    // créer la forme du boutton
    shape.setSize(sf::Vector2f(length,height));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x,y);
  }

  // En fonction de la sortie, il y aura un code dans GUI qui sera utilisé pour lancer la prochaine itération

  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
     sf::Vector2i mousePos = sf::Mouse::getPosition(window); // On traque la position de notre sourie
  
     // Regarde si : L'évènement est la pression du bouton de la souris, puis regarde si le boutton pressé est le click gauche, puis regarde si le clique ce trouve bien sur l'emplacement du boutton
    
     if (mousePos.x >= x && mousePos.x <= (x + length) && mousePos.y >= y  && mousePos.y <= (y + height)) {
      
      std::cout << "Button stop clicked" << std::endl;

      return true;
     }
    }
    return false;
  }
};