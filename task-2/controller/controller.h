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
    virtual ~Command() = default;
    virtual void execute(class SimulationController& controller, const std::string& args) = 0;
};

class TickCommand : public Command {
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

class HelpCommand : public Command {
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

class ExitCommand : public Command {
public:
    void execute(SimulationController& controller, const std::string& args) override;
};

std::unique_ptr<Command> parseCommand(const std::string& command);

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
    Game_model& getModel();
    Game_view& getView();

private:
    void runOfflineMode();
    void runInteractiveMode();
    std::unique_ptr<Game_model> model_;
    Game_view view_;
    std::string out_file;
    void printInFile(
            std::ofstream& ofile,
            const std::vector<std::vector<bool>>& field,
            const std::string& name,
            int iterations
    ) const;
};

#endif // TASK_2_CONTROLLER_H