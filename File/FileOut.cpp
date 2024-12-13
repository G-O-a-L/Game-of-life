#include "FileOut.hpp"

// Default constructor implementation
FileOut::FileOut() {}

// Writes the results to a file
void FileOut::writeResults(const std::vector<std::vector<Cell>>& tab) {
    // Display a message to indicate that results are being written to a file
    std::cout << "Writing results to file..." << std::endl;
    // Open the file in append mode
    std::ofstream file(file_in.getFilename() + "_out.txt", std::ios::app);
    // Check if the file is open
    if (file.is_open()) {
        // Write the dimensions of the grid to the file
        file << file_in.getX() << " " << file_in.getY() << "\n";
        // Iterate over each row in the grid
        for (const auto& row : tab) {
            // Iterate over each cell in the row
            for (Cell cell : row) {
                // Write the state of the cell to the file
                file << cell.getState() << " ";
            }
            // Move to the next line
            file << "\n";
        }
        // Add an extra newline for readability
        file << "\n";
        // Close the file
        file.close();
    } else {
        // Display an error message if the file cannot be opened
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }
}