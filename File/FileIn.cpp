#include "FileIn.hpp"

// Initialize static variables with default values
std::string FileIn::file_path = "";
std::string FileIn::filename = "";
std::string FileIn::content = "";
int FileIn::x = 0;
int FileIn::y = 0;

// Constructor to initialize the File object with default values
FileIn::FileIn() {
    // Check if the file path is empty
    if (file_path.empty()) {
        // Open a file dialog to select a file
        const char* path = tinyfd_openFileDialog(
            "Choose a file", // Title of the dialog
            "",                   // Initial path (empty = default directory)
            0,                    // Number of filters
            nullptr,              // Filters (e.g., {"*.txt", "*.doc"})
            nullptr,              // Filter descriptions (e.g., "Text files")
            0                     // Multiple selection mode (0 = disabled)
        );

        // Check if a file was selected
        if (path) {
            // Print the selected file path
            std::cout << "Selected File: " << path << std::endl;
            // Store the selected file path
            file_path = path;
            // Print the stored file path
            std::cout << "File Path: " << file_path << std::endl;
        }
    }
}

// Getter method to retrieve the filename
std::string FileIn::getFilename() const { return filename; }

// Getter method to retrieve the x value
int FileIn::getX() const { return x; }

// Getter method to retrieve the y value
int FileIn::getY() const { return y; }

// Getter method to retrieve the cell values
std::vector<int> FileIn::getCells() const { return cells; }

// Method to set the filename
void FileIn::setFilename() {
    // Replace backslashes with forward slashes in the file path
    std::replace(file_path.begin(), file_path.end(), '\\', '/');

    // Extract the filename from the file path
    int f_start = file_path.find_last_of('/');
    if (filename.find_first_of('.') != std::string::npos) {
        filename = file_path.substr(f_start + 1);
    } else {
        int f_end = file_path.find_last_of('.');
        filename = file_path.substr(f_start + 1, f_end - f_start - 1);
    }
}

// Method to read the content of the file
void FileIn::setContent() {
    // Open the file for reading
    std::ifstream file(file_path);
    // Check if the file was opened successfully
    if (file.is_open()) {
        // Read the file line by line
        std::string line;
        while (std::getline(file, line)) {
            // Append each line to the content string
            content += line + "\n";
        }
        // Close the file
        file.close();
    } else {
        // Print an error message if the file could not be opened
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }
}

// Method to extract x, y, and cell values from the content
void FileIn::setFields() {
    // Find the start and end positions of the x value
    size_t x_start = content.find_first_not_of(' ');
    size_t x_end = content.find_first_of(' ', x_start);

    // Find the start and end positions of the y value
    size_t y_start = content.find_first_not_of(' ', x_end);

    // Find the positions of the space and newline characters after the y value
    size_t y_end = content.find_first_of(" \n", y_start);

    // Extract the x and y values from the content
    x = std::stoi(content.substr(x_start, x_end - x_start));
    y = std::stoi(content.substr(y_start, y_end - y_start));

    // Extract the cell values from the content and store them in the cells vector
    for (char c : content.substr(y_end)) {
        // Check if the character is '0' or '1'
        if (c == '0' || c == '1') {
            // Convert the character to an integer (0 or 1) and add it to the cells vector
            cells.push_back(c - '0');
        }
    }
}