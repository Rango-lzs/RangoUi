#pragma once

#include <QMainWindow>
#include "CommandQueue.h"
#include "ExampleCommand.h"
#include "CommandScheduler.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTriggerCommand();

    void processCommandQueue();

private:
    //CommandScheduler commandScheduler;
    CommandSchedulerThread commandSchedulerThread;
    CommandQueue commandQueue;
};
