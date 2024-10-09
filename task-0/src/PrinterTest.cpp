#include <gtest/gtest.h>
#include "Printer.h"
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

TEST(Printer, PrintStatistics_SingleEntry) {
map<string, int> wordFrequency = {{"test", 1}};
int totalWords = 1;
string outputFilename = "test_output.csv";

Printer printer(outputFilename);
printer.printStatistics(wordFrequency, totalWords);

ifstream file(outputFilename);
ASSERT_TRUE(file.is_open());

// Проверяем содержимое файла
string header;
getline(file, header);
EXPECT_EQ(header, "Слово,Частота,Частота (%)");

string line;
getline(file, line);
EXPECT_EQ(line, "test,1,100.00");

file.close();
}

TEST(Printer, PrintStatistics_MultipleEntries) {
map<string, int> wordFrequency = {{"apple", 2}, {"banana", 3}, {"cherry", 1}};
int totalWords = 6;
string outputFilename = "test_output_multiple.csv";

Printer printer(outputFilename);
printer.printStatistics(wordFrequency, totalWords);

ifstream file(outputFilename);
ASSERT_TRUE(file.is_open());

string header;
getline(file, header);
EXPECT_EQ(header, "Слово,Частота,Частота (%)");

vector<string> expectedLines = {
        "banana,3,50.00",
        "apple,2,33.33",
        "cherry,1,16.67"
};

string line;
for (const auto& expectedLine : expectedLines) {
getline(file, line);
EXPECT_EQ(line, expectedLine);
}

file.close();
}
