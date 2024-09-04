#include "CommandScheduler.h"
#include <QCoreApplication>
#include <QElapsedTimer>

CommandScheduler::CommandScheduler(QObject* parent)
    : QObject(parent),
    timer(new QTimer(this)) {
    connect(timer, &QTimer::timeout, this, &CommandScheduler::executeNextCommand);
}

void CommandScheduler::addCommand(std::unique_ptr<Command> command) {
    commandQueue.push(std::move(command));
}

//void CommandScheduler::start() {
//    timer->start(100); // 设置调度循环时间间隔为100毫秒
//}

//void CommandScheduler::stop() {
//    timer->stop();
//}

void CommandScheduler::start() {
    running = true;
    QElapsedTimer timer;
    timer.start();

    while (running) {
        if (!commandQueue.empty()) {
            commandQueue.front()->execute();
            commandQueue.pop();
        }
        else
        {
            running = false;
        }

        // 控制循环频率，例如每100毫秒运行一次
        if (timer.elapsed() >= 100) {
            timer.restart();
        }

        // 处理其他事件，防止阻塞主线程
        QCoreApplication::processEvents();
    }
}

void CommandScheduler::stop() {
    running = false;
}

void CommandScheduler::executeNextCommand() {
    if (!commandQueue.empty()) {
        commandQueue.front()->execute();
        commandQueue.pop();
    }
}

/////////////////////////////////////////////////////////////
CommandSchedulerThread::CommandSchedulerThread(QObject* parent)
    : QObject(parent), running(false) {
    // 将调度器的run方法绑定到新的线程
    connect(&schedulerThread, &QThread::started, this, &CommandSchedulerThread::run);
    moveToThread(&schedulerThread);
}

CommandSchedulerThread::~CommandSchedulerThread() {
    stop();
    schedulerThread.quit();
    schedulerThread.wait();
}

void CommandSchedulerThread::addCommand(std::unique_ptr<Command> command) {
    commandQueue.push(std::move(command));
}

void CommandSchedulerThread::start() {
    running = true;
    schedulerThread.start();
}

void CommandSchedulerThread::stop() {
    running = false;
}

void CommandSchedulerThread::run() {
    while (running) {
        if (!commandQueue.empty()) {
            commandQueue.front()->execute();
            commandQueue.pop();
        }

        QThread::msleep(100); // 每100毫秒检查一次命令队列
    }
}