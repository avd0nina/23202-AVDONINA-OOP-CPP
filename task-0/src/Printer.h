#ifndef PRINTER_H
#define PRINTER_H

#include <map>
#include <string>

using namespace std;

class Printer {
public:
    Printer(const string& filename);
    void printStatistics(const map<string, int>& wordFrequency, int totalWords);

private:
    string filename;
};

#endif // PRINTER_H
