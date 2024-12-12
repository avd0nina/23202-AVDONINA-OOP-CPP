#include "controller.h"
#include "../fileparser/fileparser.h"
#include <fstream>

void TickCommand::execute(SimulationController& controller, const std::string& args) {
    int num_tick = args.empty() ? 1 : std::stoi(args);
    for (int i = 0; i < num_tick; ++i) {
        controller.getView().printFrame(
                controller.getModel().getName(),
                controller.getModel().getField(),
                controller.getModel().getGlobIteration() + 1,
                i + 1
        );
        controller.getModel().computeIteration();
    }
}

void HelpCommand::execute(SimulationController& controller, const std::string& args) {
    controller.getView().printHelp();
}

void ExitCommand::execute(SimulationController& controller, const std::string& args) {
    throw std::runtime_error("exit");
}

std::unique_ptr<Command> parseCommand(const std::string& command) {
    if (command.substr(0, 4) == "tick") {
        return std::make_unique<TickCommand>();
    } else if (command == "help") {
        return std::make_unique<HelpCommand>();
    } else if (command == "exit") {
        return std::make_unique<ExitCommand>();
    }
    throw std::invalid_argument("Unknown command");
}

Game_model& SimulationController::getModel() {
    return *model_;
}

Game_view& SimulationController::getView() {
    return view_;
}

SimulationController::SimulationController() {
    model_ = std::make_unique<Game_model>();
}

SimulationController::SimulationController(
        const std::string& infile
): SimulationController(infile, "1", "") {}

SimulationController::SimulationController(
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

void SimulationController::printInFile(
        std::ofstream& out_file,
        const std::vector<std::vector<bool>>& field,
        const std::string& name,
        int glob_iteration
) const {
    out_file << "Name: " << name << ";" << std::endl;
    out_file << "Total iteration: " << glob_iteration << ";" << std::endl;

    int size = field.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            out_file << (field[i][j] ? "*" : " ") << " ";
        }
        out_file << std::endl;
    }
}

void SimulationController::runOfflineMode() {
    std::ofstream ofile(out_file);
    if (!ofile.is_open() || out_file.size() < 5 || out_file.substr(out_file.size() - 4) != ".txt") {
        throw std::invalid_argument("Invalid output file");
    }
    for (int i = 0; i < model_->getGlobIteration(); ++i) {
        model_->computeIteration();
    }
    printInFile(ofile, model_->getField().toVector(), model_->getName(), model_->getGlobIteration());
}

void SimulationController::runInteractiveMode() {
    try {
        std::string command = "help";
        while (command != "exit") {
            if (command.substr(0, 4) == "tick") {
                int num_tick = command.size() > 4 ? parseNumber(command.substr(5)) : 1;
                for (int i = 0; i < num_tick; ++i) {
                    view_.printFrame(model_->getName(), model_->getField(), model_->getGlobIteration() + 1, i + 1);
                    model_->computeIteration();
                }
            } else if (command.substr(0, 4) == "dump") {
                if (command.size() < 6 || command.substr(command.size() - 4) != ".txt") {
                    view_.printErr("Invalid dump file name");
                } else {
                    std::ofstream ofile(command.substr(5));
                    if (ofile.is_open()) {
                        printInFile(ofile, model_->getField().toVector(), model_->getName(), model_->getGlobIteration());
                    }
                }
            } else {
                view_.printHelp();
            }
            std::getline(std::cin, command);
        }
    } catch (const std::invalid_argument& err) {
        view_.printErr(err.what());
        throw;
    }
}

void SimulationController::play_game() {
    if (!out_file.empty()) {
        runOfflineMode();
    } else {
        runInteractiveMode();
    }
}

