#pragma once

#include <vector>

#include "Cell.hpp"

using namespace std;

class Grid {
private:
    vector<vector<Cell>> crnt_tab;
    vector<vector<Cell>> next_tab;

public:
    Grid(vector<int> tab, int x, int y) {
        // Redimensionner les tableaux pour correspondre à x colonnes et y lignes
        crnt_tab.resize(y, std::vector<Cell>(x));
        next_tab.resize(y, std::vector<Cell>(x));

        // Remplir crnt_tab
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                crnt_tab[i][j] = Cell(tab[i * x + j]);
            }
        }
    }

    vector<vector<Cell>> getTab() const {
        // renvoie crnt_tab
        return crnt_tab;
    }

    void setNextTab(vector<vector<Cell>> tab) {
        // défini next_tab
        next_tab = tab;
    }

    void nextToCurrent() {
        // défini crnt_tab avec les valeurs de next_tab
        crnt_tab = next_tab;
    }

    bool checkIfSame() {
        // regarde si crnt_tab et next_tab sont identiques
        for(int i = 0; i < size(crnt_tab); i++){
            for(int j = 0; j < size(crnt_tab); j++){
                if(crnt_tab[i][j].getState() != next_tab[i][j].getState()){
                    return false;
                }
            }
        }
        return true;
    }

    void modify(int y, int x) {
        // modifie l'état de la cellule
        crnt_tab[y][x].setState(int(crnt_tab[y][x].getState() + 1) % 3); // mort -> vie -> obstacle -> mort
    }
};
