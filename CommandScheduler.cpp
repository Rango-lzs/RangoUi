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
//    timer->start(100); // ���õ���ѭ��ʱ����Ϊ100����
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

        // ����ѭ��Ƶ�ʣ�����ÿ100��������һ��
        if (timer.elapsed() >= 100) {
            timer.restart();
        }

        // ���������¼�����ֹ�������߳�
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
    // ����������run�����󶨵��µ��߳�
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

        QThread::msleep(100); // ÿ100������һ���������
    }
}