#pragma once

// Include necessary libraries for file dialogs, input/output, strings, vectors, file streams, and algorithms
#include "tinyfiledialogs.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// Define a class to handle file input
class FileIn {
    // Static variables to store file path, filename, content, x, y, and cell values
    static std::string file_path;
    static std::string filename;
    static std::string content;
    static int x;
    static int y;
    std::vector<int> cells;

public:
    // Constructor to initialize the File object with default values
    FileIn();
    // Getter method to retrieve the filename
    std::string getFilename() const;
    // Getter method to retrieve the x value
    int getX() const;
    // Getter method to retrieve the y value
    int getY() const;
    // Getter method to retrieve the cell values
    std::vector<int> getCells() const;
    // Method to set the filename
    void setFilename();
    // Method to read the content of the file
    void setContent();
    // Method to extract x, y, and cell values from the content
    void setFields();
};