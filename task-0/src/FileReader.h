#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <list>

using namespace std;

class FileReader {
public:
    FileReader(const string& filename);
    list<string> readLines();

private:
    string filename;
};

#endif // FILEREADER_H
