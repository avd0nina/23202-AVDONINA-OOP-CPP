#ifndef TASK_2_CONTROLLER_H
#define TASK_2_CONTROLLER_H

#include "../model/model.h"
#include "../view/view.h"
#include <memory>
#include <string>
#include <vector>
#include <fstream>

class Command {
public:
    virtual ~Command() = default; // virtual Указывает, что метод может быть переопределён в производных классах, принимает ссылка на объект контроллера, через который команда управляет моделью или представлением. строка аргументов, которая может содержать дополнительные данные для выполнения команды.
    virtual void execute(class SimulationController& controller, const std::string& args) = 0;
};

// TickCommand, HelpCommand, ExitCommand — это конкретные команды, которые наследуют абстрактный класс Command.
//void execute(SimulationController& controller, const std::string& args) override; — Каждая из этих команд реализует метод execute, который будет действовать на объекте SimulationController

class TickCommand : public Command { // Выполняет шаг симуляции
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

class HelpCommand : public Command { // Печатает информацию о доступных командах.
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

class ExitCommand : public Command { // Выход из программы.
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

std::unique_ptr<Command> parseCommand(const std::string& command); // Функция возвращает умный указатель на объект типа Command. Это будет безопасно управлять памятью для команды.
//  Функция, которая принимает строку с командой, анализирует её и возвращает соответствующий объект команды

class SimulationController {
public:
    SimulationController();
    explicit SimulationController(const std::string& infile);
    SimulationController(
            const std::string& infile,
            const std::string& ticks,
            const std::string& outfile
    );
    void play_game();
    Game_model& getModel(); // Возвращает ссылку на объект модели игры.
    Game_view& getView(); // Возвращает ссылку на объект представления игры.

private:
    void runOfflineMode(); // Метод для запуска игры в оффлайн-режиме.
    void runInteractiveMode(); // Метод для запуска игры в интерактивном режиме, например, с командным интерфейсом.
    std::unique_ptr<Game_model> model_; // Умный указатель на объект модели игры, который будет управлять состоянием игры.
    Game_view view_; // Представление, которое отображает текущее состояние игры пользователю.
    std::string out_file; // Имя выходного файла для записи результатов игры.
    void printInFile( // Метод для записи состояния поля в файл.
            std::ofstream& ofile,
            const Field &field,
            const std::string& name,
            int iterations
    ) const;
};

#endif // TASK_2_CONTROLLER_H