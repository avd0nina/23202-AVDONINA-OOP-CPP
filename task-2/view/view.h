#ifndef TASK_2_VIEW_H
#define TASK_2_VIEW_H

#pragma once
#include "../model/model.h"
#include <iostream>
#include <string>

class Game_view {
public:
    static void printErr(const std::string& err_message) ;
    static void printHelp() ;
    static void printFrame(
            const std::string& name,
            const Field& field,
            int glob_iteration,
            int curr_iteration
    ) ;
};

#endif //TASK_2_VIEW_H
