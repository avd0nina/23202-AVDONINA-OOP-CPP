#include "FileReader.h"
#include "Parser.h"
#include "Statistic.h"
#include "Printer.h"
#include <iostream>

using namespace std;

int main(int arguments_number, char* arguments[]) {
    if (arguments_number != 3) {
        cerr << "Usage: " << arguments[0] << " input.txt output.csv\n";
        return 1;
    }

    FileReader fileReader(arguments[1]);
    list<string> lines = fileReader.readLines();
    if (lines.empty()) {
        return 1;
    }

    Parser parser;
    Statistic statistic;
    for (const string& line : lines) {
        list<string> words = parser.splitIntoWords(line);
        statistic.processWords(words);
    }

    Printer printer(arguments[2]);
    printer.printStatistics(statistic.getWordFrequency(), statistic.getTotalWords());

    return 0;
}
