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
  sf::Text text;
  sf::Font sharedFont;

public:
  virtual ~Button() {}

  bool virtual handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

  void draw(sf::RenderWindow& window){
    window.draw(shape); // Dessine le boutton
    window.draw(text);  // Dessine le texte
  }
};


/************************************************************************************************************/

class ButtonNext : public Button{
public:
  ButtonNext() {}

  ~ButtonNext() {}

  ButtonNext(int y, float length, float height) {
    // Le boutton next sera à 5 pixel du bord de la fenêtre
    int x = 5;

    // créer la forme du boutton
    shape.setSize(sf::Vector2f(length,height));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x,y);

    // Séléction de la police d'écriture
    if(!sharedFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
      // Gestion d'erreur si la police ne charge pas
      throw std::runtime_error("Impossible de charger la police");
    }

    // Paramétrage de la police d'écriture

    text.setFont(sharedFont); // Indique la police du texte

    text.setString("next"); /// Ce que l'on écris

    text.setCharacterSize(12); // La taille de la police

    text.setFillColor(sf::Color::White); // couleur du texte

    // Centrer le texte de surle boutton (méthode de Set Origin)

    sf::FloatRect textBounds = text.getLocalBounds(); // Permet d'obtenir les bordures de notre boutton
      
    text.setPosition(y + 3, x + 2); // On écris le texte sur le bouton
  }

  // En fonction de la sortie, il y aura un code dans GUI qui sera utilisé pour lancer la prochaine itération

  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Regarde si : L'évènement est la pression du bouton de la souris, puis regarde si le boutton pressé est le click gauche, puis regarde si le clique ce trouve bien sur l'emplacement du boutton
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shape.getGlobalBounds().contains(mousePos.x, mousePos.y) == 1) {
      std::cout << "Button next clicked" << std::endl;
      return true;
    }
    return false;}
};

/*********************************************************************************************************/

class ButtonStop : public Button{
public:
  ButtonStop() {}

  ~ButtonStop() {}

  // Paramêtres : y origin | longueur du bouton | largueur du bouton, notre bouton est donc custom
  ButtonStop(int y, float length, float height) { // Le y est toujours le même
    // Le boutton next sera à 80 pixel du bord de la fenêtre
    int x = 80;

    // créer la forme du boutton
    shape.setSize(sf::Vector2f(length,height));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x,y);

    // Séléction de la police d'écriture
    if(!sharedFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")){
      // Gestion d'erreur si la police ne charge pas
      throw std::runtime_error("Impossible de charger la police");
    }
    
    // Paramétrage de la police d'écriture

    text.setFont(sharedFont); // Indique la police du texte

    text.setString("stop"); /// Ce que l'on écris

    text.setCharacterSize(12); // La taille de la police

    text.setFillColor(sf::Color::White); // couleur du texte

    // Centrer le texte de surle boutton (méthode de Set Origin)

    sf::FloatRect textBounds = text.getLocalBounds(); // Permet d'obtenir les bordures de notre boutton
      
    text.setPosition(y + 3, x + 2); // On écris le texte sur le bouton
  }

  // En fonction de la sortie, il y aura un code dans GUI qui sera utilisé pour lancer la prochaine itération

  bool handleEvent(sf::Event& event, sf::RenderWindow& window) override {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Regarde si : L'évènement est la pression du bouton de la souris, puis regarde si le boutton pressé est le click gauche, puis regarde si le clique ce trouve bien sur l'emplacement du boutton
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shape.getGlobalBounds().contains(mousePos.x, mousePos.y) == 1) {
      std::cout << "Button stop clicked" << std::endl;
      return true;
    }
    return false;
  }
};