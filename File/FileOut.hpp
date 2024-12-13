#pragma

#include <vector>
#include <fstream>

#include "FileIn.hpp"
#include "Cell.hpp"

// Class responsible for writing results to a file
class FileOut {
private:
    // Object to handle file input
    FileIn file_in;
    // Object to represent a cell
    Cell cell;
public:
    // Default constructor
    FileOut();
    // Method to write results to a file
    void writeResults(const std::vector<std::vector<Cell>>& tab);
};