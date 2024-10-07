#include "FileReader.h"
#include <fstream>
#include <iostream>

using namespace std;

FileReader::FileReader(const string& filename) : filename(filename) {}

list<string> FileReader::readLines() {
    list<string> lines;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return lines;
    }
    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}
