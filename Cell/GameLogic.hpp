#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <tbb/tbb.h>
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

        size_t xLeft, xRight, yUp, yDown;

        tbb::parallel_for(size_t(0),current_tab.size(),[&](size_t y) {
            for (size_t(x) = 0; x < xmax; x++) {
                int cpt = 0;
                size_t yUp = (y == 0) ? ymax - 1 : y - 1;
                size_t yDown = (y + 1) % ymax;
                size_t xLeft = (x == 0) ? xmax - 1 : x - 1;
                size_t xRight = (x + 1) % xmax;

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
        });

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