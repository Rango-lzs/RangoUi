#pragma once
#include "ICommnand.h"

class CommandFactory {
public:
    using CommandCreator = std::function<ICommand*()>;

    static CommandFactory& instance() {
        static CommandFactory factory;
        return factory;
    }

    void registerCommand(const QString& commandName, CommandCreator creator) {
        commandMap[commandName] = creator;
    }

    ICommand* createCommand(const QString& commandName) {
        if (commandMap.contains(commandName)) {
            return commandMap[commandName]();
        }
        return nullptr;
    }

private:
    QMap<QString, CommandCreator> commandMap;
};