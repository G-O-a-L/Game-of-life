#pragma

#include <vector>
#include <stdexcept>
#include <iostream>

#include "Grid.hpp"

using namespace std;


class GameLogic : public Grid{
    public:
        GameLogic(vector<int> cells, int x/*x max*/, int y/*y max*/) : Grid(cells, x/*x max*/, y/*y max*/){}

        void nextStep(const bool mode){
            // génération suivante
            int xmax/*pour x*/, ymax/*pour y*/;
            std::vector<std::vector<Cell>> current_tab = getTab(); /// Accède au tableau crnt
            std::vector<std::vector<Cell>> next_tab = getTab(); /// Accède au tableau crnt

            xmax = current_tab[0].size();
            ymax = current_tab.size();
            //Calcul de la prochaine étape

            for(int y = 0; y < ymax; y++){
                for(int x = 0; x < xmax; x++){
                    std::cout << "Ite " << y << std::endl;
                    int cpt = 0;
                    if(current_tab[y-1 % ymax][x-1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y % ymax][x-1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y+1 % ymax][x-1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y-1 % ymax][x % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y+1 % ymax][x % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y-1 % ymax][x+1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y % ymax][x+1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y+1 % ymax][x+1 % xmax].getState() == 1){
                        cpt += 1;
                    }
                    if(current_tab[y][x].getState() == 1 && cpt != 2 && cpt != 3 ){
                        std::cout << "Cellule morte" << std::endl;
                        next_tab[y][x].setState(0);           
                    }
                    else if(current_tab[y][x].getState() == 0 && cpt == 3 ){
                        std::cout << "Cellule vivante" << std::endl;
                        next_tab[y][x].setState(1);       
                    }
                    std::cout << "Itex " << x << std::endl;
                }
            }
            std::cout << "Fin de la génération" << std::endl;

            setNextTab(next_tab);

            if(mode == 1){
                // GUI : 1
                if(checkIfSame()){
                    throw runtime_error("Fin du programme, les deux dernière étapes sont identiques");
                }
            }
            nextToCurrent();
        }
};