#include "File.h"

// Constructor to initialize the File object with default values
File::File() : content(""), filename(""), x(0), y(0), cells() {}

// Destructor to free up resources when the File object is destroyed
File::~File() {}

// Sets the filename for the File object
void File::setFilename(const std::string& filename) {
    this->filename = filename;
}

// Reads the content of the file and stores it in the content variable
void File::getContent() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    }
}

// Extracts the x and y values from the content and stores them in the x and y variables
// Also extracts the cell values and stores them in the cells vector
void File::setFields() {
    // Find the start and end positions of the x value
    size_t x_start = content.find_first_not_of(' ');
    size_t x_end = content.find_first_of(' ', x_start);

    // Find the start and end positions of the y value
    size_t y_start = content.find_first_not_of(' ', x_end);
    size_t y_end;

    // Find the positions of the space and newline characters after the y value
    size_t space_pos = content.find_first_of(' ', y_start);
    size_t newline_pos = content.find_first_of('\n', y_start);

    // Determine the end position of the y value
    if (space_pos == std::string::npos) {
        // Only the newline character is found
        y_end = newline_pos;
    } else {
        // Both space and newline characters are found, compare their distances
        if (y_start - space_pos < y_start - newline_pos) {
            y_end = space_pos;
        } else {
            y_end = newline_pos;
        }
    }

    // Extract the x and y values from the content
    x = std::stoi(content.substr(x_start, x_end - x_start));
    y = std::stoi(content.substr(y_start, y_end - y_start));

    // Extract the cell values from the content and store them in the cells vector
    for (char c : content.substr(y_end)) {
        // Check if the character is '0' or '1'
        if (c == '0' || c == '1') {
            cells.push_back(c - '0'); // Convert char to int (0 or 1)
        }
    }
}

// Writes the results to a file
void File::writeResults(const std::vector<std::vector<int>>& tab) {
    std::ofstream file(filename + "_out");
    for (const auto& row : tab) {
        for (int cell : row) {
            file << cell;
            file << " ";
        }
        file << "\n";
    }
    file.close();
}