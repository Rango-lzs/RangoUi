#pragma once

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0; // 具体命令需要实现的执行方法
};
