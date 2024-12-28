#ifndef TASK_2_FILEPARSER_H
#define TASK_2_FILEPARSER_H

#include "../model/model.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

struct UniverseConfig { // структура, содержащая конфигурацию "вселенной".
    std::string name;
    std::string b_rule;
    std::string s_rule;
    std::vector<Point> coordinates;
};

int parseNumber(const std::string& str); // декларация вспомогательной функции, которая преобразует строку str в целое число (int).

class FileParser { // Класс FileParser для разбора (парсинга) файлов конфигурации вселенной.
public:
    static UniverseConfig parseFile(const std::string& infile); // Статический метод, не требует создания объекта FileParser для вызова.
    // Принимает имя входного файла infile.
    // Возвращает объект структуры UniverseConfig, содержащий имя, правила (b_rule, s_rule) и координаты точек, считанные из файла.
};

#endif //TASK_2_FILEPARSER_H