#pragma once

#include "Button.hpp"
#include "GameLogic.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include<stdexcept>

class GUI{
private:
    GameLogic& gameLogic;

    int cell_size;
    int length;
    int height;

    sf::RenderWindow window;
    
    std::vector<int> cellstate;   // Pour des fins de tests, je simule la grille ***test
    std::vector<std::vector<int>> grid; // Pour simuler l'entrée d'une grille ***test

    sf::Vector2i mousePosition; // Vecteur qui sert à stocker al position actuelle 

public:

    ButtonNext next;
    ButtonStop stop;

    // Constructeur de GUI

    GUI(int xmax, int ymax, GameLogic& gameLogic) : 
        cell_size(1000/int(xmax * ymax)), /*Adapte la taille des cellules en fonction du nombre de cellule demandé*/
        length(xmax),/* Le nombre de  ligne  */
        height(ymax),/* Le nombre de  colone */
        gameLogic(gameLogic), /*Notre gameLogic*/
        window(sf::VideoMode(xmax * cell_size, ymax * cell_size + 50)/* + 50 = taille de la banderole à mettre sous la grille pour mettre les bouttons next et stop*/, "Game of Life, groupe 4" ) {

        // Initialise notre boutton
        next = ButtonNext(height * cell_size + 2/*Calcul de la hauteur de la grille de cllule, on rajoute 2 pour pouvoir créer uue petite marge*/);
        stop = ButtonStop(height * cell_size + 2/*même raison*/); // y origin // largeur // longueur
    }


    void RenderWindow() {
        window.clear(); // La fenêtre est clear, prête pour être redessinée

        sf::RectangleShape bottom_stripe(sf::Vector2f(length * cell_size, 50));
        sf::RectangleShape cell(sf::Vector2f(cell_size - 1.0f, cell_size - 1.0f));
        sf::RectangleShape cell_obstacle(sf::Vector2f(cell_size - 1.0f, cell_size - 1.0f));

        static const sf::Color bg(192,192,192);
        static const sf::Color color_obs(65,105,225);



        cell.setFillColor(sf::Color::White);
        cell_obstacle.setFillColor(color_obs);
        bottom_stripe.setFillColor(bg);

        std::vector<std::vector<Cell>> to_render = gameLogic.getTab(); // Permet de recevoir la version crnt de tab, qu'il faut ensuite lire

        if (to_render.empty()) {
            throw std::runtime_error("Invalid array, can't display nothing");
        }

        // Dessine l'ensemble des cases en fonction de l'état des cellules
        for (int y = 0; y < to_render.size(); y++) { // Pour chaque ligne, jusqu'à la ligne max
            for (int x = 0; x < to_render[0].size(); x++) { // Pour chaque colonne jusqu'à la colone max
                // Si la cellule est vivante
                if (to_render[y][x].getState() == 1) {
                    cell.setPosition(x * cell_size, y * cell_size);
                    window.draw(cell);
                }
                // Si la cellule est morte
                else if (to_render[y][x].getState() != 0 && to_render[y][x].getState() != 1) { // Si la cellule est une cellule obstacle
                    cell_obstacle.setPosition(x * cell_size, y * cell_size);
                    window.draw(cell_obstacle);
                }
            }
        }
        bottom_stripe.setPosition(0, cell_size * height);
        window.draw(bottom_stripe); // Dessine la bande du bas

        next.draw(window); // Dessine le boutton next
        stop.draw(window); // Dessine le boutton stop

        window.display(); // Montre la fenêtre qui vient d'être dessinée
    }

    void run() {
        float temporal_step;
        // Demande du pas temporel entre itérations
        std::cout << "Pas temporel ? (en ms) : ";
        std::cin >> temporal_step;

        sf::Clock clock; // Créer un objet qui va suivre le temps
    
        while (window.isOpen()) {
            sf::Event event;
            static bool bstop = 0; // On commence avec la GUI qui n'est pas en pause
            while (window.pollEvent(event)) {
                // Si la fenêtre est fermée, on ferme la fenêtre
                if (event.type == sf::Event::Closed) window.close();

                if (stop.handleEvent(event, window)) { // Si c'est le boutton stop qui est pressé
                    bstop = !bstop;
                    clock.restart(); // Reset le compteur
                }

                if (bstop) { // Si bstop = true donc si le jeu est en pause

                    // Only mark for render if next button is clicked
                    if (next.handleEvent(event, window)) {
                        gameLogic.nextStep(1); // Itération suivante
                        RenderWindow();
                    }

                     // Check si une cellule fut cliquée
                     if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                     mousePosition = sf::Mouse::getPosition(window);

                     // Si nous avons cliqué sur la zone de la grille de cellule :
                     if (mousePosition.x <= length * cell_size && mousePosition.x > 0 && mousePosition.y <= height * cell_size && mousePosition.y > 0) {
                        // On modifie la cellule sur laquelle on a cliqué pour la prochaine itération
                        gameLogic.modify(int(mousePosition.y / cell_size),int(mousePosition.x / cell_size));

                        RenderWindow();
                     }
                    }
                }
            }

            if (!bstop) { // Si l'on n'est pas en pause
                // Délai 
                if (clock.getElapsedTime().asMilliseconds() >= temporal_step) {
                    gameLogic.nextStep(1); // à la fin du délai, on passe à l'itération suivante
                    RenderWindow();
                    clock.restart(); // Reset le compteur
                }
            }
            sf::sleep(sf::milliseconds(10));
        }
    }
};
