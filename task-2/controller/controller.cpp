#include "controller.h"
#include "../fileparser/fileparser.h"
#include <fstream>

void TickCommand::execute(SimulationController& controller, const std::string& args) {
    int num_tick = args.empty() ? 1 : std::stoi(args); // Если аргумент команды пуст (нет числа), то по умолчанию выполняется 1 шаг (tick). Иначе, из строки аргумента парсится целое число (num_tick).
    for (int i = 0; i < num_tick; ++i) {
        controller.getView().printFrame( // На каждой итерации цикла вызывается метод printFrame у объекта view_ контроллера. Этот метод отвечает за вывод состояния игры.
                controller.getModel().getName(), //  возвращает имя игры
                controller.getModel().getField(), // возвращает текущее игровое поле
                controller.getModel().getGlobIteration() + 1, // общее количество итераций
                i + 1 // индекс текущей итерации
        );
        controller.getModel().computeIteration(); // После вывода текущего состояния, метод computeIteration вызывается для модели игры.
        // Этот метод производит один шаг симуляции: вычисляет следующее состояние игрового поля на основе текущего состояния
    }
}

void HelpCommand::execute(SimulationController& controller, const std::string& args) {
    controller.getView().printHelp(); // вызывается printHelp из представления (view_)
}

void ExitCommand::execute(SimulationController& controller, const std::string& args) {
    throw std::runtime_error("exit"); //  выбрасывается исключение std::runtime_error с сообщением "exit", которое сигнализирует о завершении работы.
}

std::unique_ptr<Command> parseCommand(const std::string& command) { // Функция для парсинга строки команды и создания соответствующего объекта команды
    if (command.substr(0, 4) == "tick") {
        return std::make_unique<TickCommand>();
    } else if (command == "help") {
        return std::make_unique<HelpCommand>();
    } else if (command == "exit") {
        return std::make_unique<ExitCommand>();
    }
    throw std::invalid_argument("Unknown command");
}

Game_model& SimulationController::getModel() { // Возвращает ссылку на объект модели игры.
    return *model_;
}

Game_view& SimulationController::getView() { // Возвращает ссылку на объект представления игры.
    return view_;
}

SimulationController::SimulationController() { // Конструктор по умолчанию
    model_ = std::make_unique<Game_model>();
}

SimulationController::SimulationController( // Конструктор, принимающий имя входного файла.
        const std::string& infile
): SimulationController(infile, "1", "") {}

SimulationController::SimulationController( // Конструктор, который принимает входной файл, количество шагов и выходной фай
        const std::string& infile,
        const std::string& ticks,
        const std::string& outfile
) {
    try {
        int tick = parseNumber(ticks);
        UniverseConfig config = FileParser::parseFile(infile);
        model_ = std::make_unique<Game_model>(
                config.name,
                config.b_rule,
                config.s_rule,
                config.coordinates
        );
        out_file = outfile;
    } catch (const std::invalid_argument& err) {
        view_.printErr(err.what());
        throw;
    }
}

void SimulationController::printInFile( // Печатает состояние игры в файл
        std::ofstream& out_file,
        const Field &field,
        const std::string& name,
        int glob_iteration
) const {
    out_file << "Name: " << name << ";" << std::endl;
    out_file << "Total iteration: " << glob_iteration << ";" << std::endl;
    for (int i = -1; i <= field.getSize(); ++i) { // нешний цикл, который итерирует по строкам поля. Переменная i будет изменяться от -1 до field.getSize().
        for (int j = -1; j <= field.getSize(); ++j) { // внутренний цикл, который итерирует по столбцам поля.
            if (field.getState(i, j)) { // вызывает метод getState объекта field для получения состояния клетки в строке i и столбце j. Если клетка живая, то метод возвращает true, если мертвая — false.
                out_file << "* "; // Если клетка живая (метод getState возвращает true), то в файл записывается символ "* "
            } else {
                out_file << "  "; // в файл записывается строка с двумя пробелами " "
            }
        }
        out_file << std::endl;
    }
}

void SimulationController::runOfflineMode() { //  выполняет симуляцию в офлайн-режиме, рассчитывает несколько итераций на основе модели и записывает результаты в выходной фай
    std::ofstream ofile(out_file); // Создается объект ofstream (поток для записи в файл) для открытия файла, указанного в переменной out_file.
    if (!ofile.is_open() || out_file.size() < 5 || out_file.substr(out_file.size() - 4) != ".txt") {
        throw std::invalid_argument("Invalid output file");
    }

    for (int i = 0; i < model_->getGlobIteration(); ++i) { // Запускается цикл, который будет выполняться столько раз, сколько итераций определено в модели.
        model_->computeIteration();
    }

    printInFile(ofile, model_->getField(), model_->getName(), model_->getGlobIteration()); // После выполнения всех итераций данные модели (включая текущее состояние поля, имя модели и количество глобальных итераций) записываются в файл ofile
}

void SimulationController::runInteractiveMode() { // запускает симуляцию в интерактивном режиме, позволяя пользователю вводить команды и управлять процессом симуляции.
    try {
        std::string command = "help";
        while (command != "exit") {
            try {
                std::string command_name = command.substr(0, command.find(' '));
                std::string args = command.size() > command_name.size() ? command.substr(command_name.size() + 1) : "";
                std::unique_ptr<Command> command = parseCommand(command_name);
                command->execute(*this, args);
            } catch (const std::invalid_argument& err) {
                view_.printErr(err.what());
            }
            std::getline(std::cin, command);
        }
    } catch (const std::runtime_error& err) {
        if (std::string(err.what()) != "exit") {
            view_.printErr(err.what());
            throw;
        }
    }
}

void SimulationController::play_game() {
    if (!out_file.empty()) {
        runOfflineMode();
    } else {
        runInteractiveMode();
    }
}

