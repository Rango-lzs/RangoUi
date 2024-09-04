// MainWindow.cpp
#include "MainWindow.h"
#include <QMenuBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 创建菜单或按钮并连接信号槽
    QMenu *menu = menuBar()->addMenu(tr("Commands"));
    QAction *exampleAction1 = menu->addAction(tr("Trigger Command1"));
    QAction* exampleAction2 = menu->addAction(tr("Trigger Command2"));
    QAction* exampleAction3 = menu->addAction(tr("Trigger Command3"));

    connect(exampleAction1, &QAction::triggered, this, &MainWindow::onTriggerCommand);
    connect(exampleAction2, &QAction::triggered, this, &MainWindow::onTriggerCommand);
    connect(exampleAction3, &QAction::triggered, this, &MainWindow::onTriggerCommand);

    // 开始命令调度循环
    //commandScheduler.start();
    commandSchedulerThread.start();

	// 设置定时器来定期调度命令
	//QTimer* timer = new QTimer(this);
	//connect(timer, &QTimer::timeout, this, &MainWindow::processCommandQueue);
	//timer->start(2000); // 每100毫秒检查一次命令队列
}

MainWindow::~MainWindow() {}

void MainWindow::onTriggerCommand() {
    // 创建并加入命令队列
    //commandScheduler.addCommand(std::make_unique<ExampleCommand>());
    //commandScheduler.start()
    commandSchedulerThread.addCommand(std::make_unique<ExampleCommand>());
}

// 在某个时机（例如定时器或用户操作后）执行命令
void MainWindow::processCommandQueue() {
	// 调度并执行命令
	commandQueue.executeNext();
}