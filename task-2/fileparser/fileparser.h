#ifndef TASK_2_FILEPARSER_H
#define TASK_2_FILEPARSER_H

#include "../model/model.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

struct UniverseConfig {
    std::string name;
    std::string b_rule;
    std::string s_rule;
    std::vector<Point> coordinates;
};

int parseNumber(const std::string& str);

class FileParser {
public:
    static UniverseConfig parseFile(const std::string& infile);
};

#endif //TASK_2_FILEPARSER_H