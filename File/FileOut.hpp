#pragma

#include <vector>
#include <fstream>

#include "FileIn.hpp"
#include "Cell.hpp"

class FileOut {
private:
    FileIn file_in;
    Cell cell;
public:
    FileOut();
    void writeResults(const std::vector<std::vector<Cell>>& tab);
};

FileOut::FileOut() {}

// Writes the results to a file
void FileOut::writeResults(const std::vector<std::vector<Cell>>& tab) {
    std::cout << "Writing results to file..." << std::endl;
    std::ofstream file(file_in.getFilename() + "_out.txt");
    file << file_in.getX() << " " << file_in.getY() << "\n";
    for (const auto& row : tab) {
        for (Cell cell : row) {
            file << cell.getState() << " ";
        }
        file << "\n";
    }
    file << "\n";
    file.close();
}