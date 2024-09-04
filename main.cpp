#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}

//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//
//    ProfileManager profileManager;
//    ResourcePool resourcePool;
//    ActionPool actionPool;
//
//    profileManager.loadProfile("Actions.xml");
//    QDomDocument actionsDoc = profileManager.getProfile("Actions.xml");
//
//    QMainWindow mainWindow;
//    actionPool.loadActions(actionsDoc, &mainWindow, &resourcePool);
//
//    // 创建工具栏并添加Actions
//    QToolBar* toolBar = mainWindow.addToolBar("MainToolBar");
//    toolBar->addAction(actionPool.getAction("ID !AsAlnHandle"));
//
//    mainWindow.show();
//    return app.exec();
//}