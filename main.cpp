// main global de GoL
#include "View.hpp"

int unitTest() {
    vector<vector<Cell>> grid = {
        0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0
    }
}

int main() {
    View view;
    if (view.unitTest()) {
        cout << "Test passed" << endl;
        view.run();
    }
}