#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

#include "Grid.hpp"

using namespace std;

class GameLogic : public Grid {
public:
    GameLogic(vector<int> cells, int x /*x max*/, int y /*y max*/) : Grid(cells, x /*x max*/, y /*y max*/) {}

    void nextStep(const bool mode) {
        // génération suivante
        int xmax /*pour x*/, ymax /*pour y*/;
        std::vector<std::vector<Cell>> current_tab = getTab(); // Accède au tableau crnt
        std::vector<std::vector<Cell>> next_tab = getTab(); // Accède au tableau crnt

        xmax = current_tab[0].size();
        ymax = current_tab.size();
        // Calcul de la prochaine étape

        int xLeft, xRight, yUp, yDown;

        for (int y = 0; y < ymax; y++) {
            for (int x = 0; x < xmax; x++) {
                int cpt = 0;

                if (y - 1 < 0) {
                    yUp = ymax - 1; // Prise en charge des indices négatif pour avoid segmentation fault
                } else {
                    yUp = y-1;
                }

                yDown = (y + 1) % ymax;

                if (x-1 < 0) {
                    xLeft = xmax - 1; // Prise en charge des indices négatif pour avoid segmentation fault
                } else {
                    xLeft = x-1;
                }

                xRight = (x + 1) % xmax;

                if (current_tab[yDown][x].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[yUp][x].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[yUp][xLeft].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[y][xLeft].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[yDown][xLeft].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[yUp][xRight].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[y][xRight].getState() == 1) {
                    ++cpt;
                }
                if (current_tab[yDown][xRight].getState() == 1) {
                    ++cpt;
                }

                // Si la cellule actuelle est vivante
                if (current_tab[y][x].getState() == 1 && cpt != 2 && cpt != 3 ) {
                    next_tab[y][x].setState(0);           
                }
                // Si la cellule actuelle est morte
                else if (current_tab[y][x].getState() == 0 && cpt == 3) {
                    next_tab[y][x].setState(1);       
                }
            }
        }

        setNextTab(next_tab);

        if (mode == 1) {
            // GUI : 1
            if (checkIfSame()) {
                throw runtime_error("Fin du programme, les deux dernière étapes sont identiques");
            }
        }
        nextToCurrent();
    }
};