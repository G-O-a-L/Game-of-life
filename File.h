#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class File {
    std::string content;
    std::string filename;
    int x;
    int y;
    std::vector<int> cells;

public:
    File();
    ~File();
    void setFilename(const std::string& filename);
    void getContent();
    void setFields();
    void writeResults(const std::vector<std::vector<int>>& tab);
};