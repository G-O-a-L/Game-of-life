#include "FileIn.hpp"
#include "FileOut.hpp"

int main() {
    FileIn filein;
    FileOut fileout;

    filein.setFilename();
    filein.setContent();
    filein.setFields();
    std::cout << filein.getX() << std::endl;
    std::cout << filein.getY() << std::endl;
    fileout.writeResults(filein.getCells());

    return 0;
}