#include "Printer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>

using namespace std;

Printer::Printer(const string& filename) : filename(filename) {}

void Printer::printStatistics(const map<string, int>& wordFrequency, int totalWords) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Cannot open output file.\n";
        return;
    }
    list<pair<string, int>> sortedWords(wordFrequency.begin(), wordFrequency.end());
    sortedWords.sort([](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second;
    });

    outputFile << "Слово,Частота,Частота (%)\n";
    for (const auto& entry : sortedWords) {
        outputFile << entry.first << "," << entry.second << ","
                   << fixed << setprecision(2)
                   << (static_cast<double>(entry.second) / totalWords) * 100 << "\n";
    }
    outputFile.close();
    cout << "Файл " << filename << " успешно создан.\n";
}

