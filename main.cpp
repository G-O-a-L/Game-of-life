// main global de GoL
#include "View.hpp"

int main() {
    View view;
    if (view.unitTest()) {
        cout << "Test passed" << "\n" << endl;
        view.run();
    }
}