// CommandQueue.h
#pragma once
#include "Command.h"
#include <queue>
#include <memory>

class CommandQueue {
public:
    void addCommand(std::unique_ptr<Command> command) {
        commands.push(std::move(command));
    }

    void executeNext() {
        if (!commands.empty()) {
            commands.front()->execute();
            commands.pop();
        }
    }

private:
    std::queue<std::unique_ptr<Command>> commands;
};
