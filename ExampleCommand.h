#pragma once
#include "Command.h"
#include <QDebug>

class ExampleCommand : public Command {
public:
    void execute() override {
        qDebug() << "Executing ExampleCommand...";
        // 在这里实现具体命令的逻辑
    }
};
