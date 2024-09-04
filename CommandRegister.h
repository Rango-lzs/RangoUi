#pragma once

template <typename T>
class CommandRegister {
public:
    CommandRegister(const QString& commandName) {
        CommandFactory::instance().registerCommand(commandName, []() -> ICommand* {
            return new T();
        });
    }
};
