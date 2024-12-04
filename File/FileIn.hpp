#pragma once

#include "tinyfiledialogs.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class FileIn {
    static std::string file_path;
    static std::string filename;
    static std::string content;
    static int x;
    static int y;
    std::vector<int> cells;

public:
    FileIn();
    std::string getFilename() const;
    int getX() const;
    int getY() const;
    std::vector<int> getCells() const;
    void setFilename();
    void setContent();
    void setFields();
};

std::string FileIn::file_path = "";
std::string FileIn::filename = "";
std::string FileIn::content = "";
int FileIn::x = 0;
int FileIn::y = 0;

// Constructor to initialize the File object with default values
FileIn::FileIn() {
    if (file_path.empty()) {
        //while (true) {
            // Titre et chemin initial
            const char* path = tinyfd_openFileDialog(
            "Choose a file", // Titre de la fenêtre
            "",                   // Chemin initial (vide = dossier par défaut)
            0,                    // Nombre de filtres
            nullptr,              // Filtres (ex: {"*.txt", "*.doc"})
            nullptr,              // Description du filtre (ex: "Fichiers texte")
            0                     // Mode de sélection multiple (0 = désactivé)
            );

            if (path) {
                std::cout << "Selected File: " << path << std::endl;
                file_path = path;
                std::cout << "File Path: " << file_path << std::endl;
                //break;
            }
        //}
    }
}

// Getter methods to retrieve the x, y, and cell values of the File object
std::string FileIn::getFilename() const { return filename; } // Returns the x value

int FileIn::getX() const { return x; } // Returns the x value

int FileIn::getY() const { return y; } // Returns the y value

std::vector<int> FileIn::getCells() const { return cells; } // Returns the cell values

// Sets the filename for the File object
void FileIn::setFilename() {
    std::replace(file_path.begin(), file_path.end(), '\\', '/');

    // Extraire le nom du fichier sans le chemin
    int f_start = file_path.find_last_of('/');
    if (filename.find_first_of('.') != std::string::npos) {
        filename = file_path.substr(f_start + 1);
    } else {
        int f_end = file_path.find_last_of('.');
        filename = file_path.substr(f_start + 1, f_end - f_start - 1);
    }
}

// Reads the content of the file and stores it in the content variable
void FileIn::setContent() {
    std::ifstream file(file_path);
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
void FileIn::setFields() {
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