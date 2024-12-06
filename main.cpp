// Main entry point of the Game of Life application
#include "View.hpp"

int main() {
    // Create an instance of the View class
    View view;
    // Run unit tests to verify the application's functionality
    if (view.unitTest()) {
        // If all tests pass, display a success message
        cout << "Test passed" << "\n" << endl;
        // Start the application's main loop
        view.run();
    }
}