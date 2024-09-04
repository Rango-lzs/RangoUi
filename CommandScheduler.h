#pragma once
#include "Command.h"
#include <queue>
#include <memory>
#include <QObject>
#include <QTimer>
#include <QThread>

class CommandScheduler : public QObject {
    Q_OBJECT

public:
    CommandScheduler(QObject *parent = nullptr);
    void addCommand(std::unique_ptr<Command> command);
    void start();
    void stop();

private slots:
    void executeNextCommand();

private:
    std::queue<std::unique_ptr<Command>> commandQueue;
    QTimer *timer;
    bool running;
};


class CommandSchedulerThread : public QObject {
    Q_OBJECT

public:
    CommandSchedulerThread(QObject* parent = nullptr);
    ~CommandSchedulerThread();
    void addCommand(std::unique_ptr<Command> command);
    void start();
    void stop();

private:
    void run(); // 调度循环方法

    std::queue<std::unique_ptr<Command>> commandQueue;
    QThread schedulerThread;
    bool running;
};