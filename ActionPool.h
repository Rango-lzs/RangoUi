#pragma once

#include <QAction>
#include <QDomDocument>

class ActionPool {
public:
    void loadActions(const QDomDocument& actionsDoc, QWidget* parent, ResourcePool* resourcePool) {
        QDomNodeList actionNodes = actionsDoc.elementsByTagName("Action");
        for (int i = 0; i < actionNodes.count(); ++i) {
            QDomElement element = actionNodes.at(i).toElement();
            QString name = element.attribute("name");

            QAction* action = new QAction(parent);
            action->setText(element.firstChildElement("Text").firstChildElement("Menu").text());
            action->setIcon(resourcePool->getIcon(name));
            action->setStatusTip(resourcePool->getHint(name));

            QString script = element.firstChildElement("script").text();
            connect(action, &QAction::triggered, [script]() {
                ICommand* command = CommandFactory::instance().createCommand(script);
                if (command) {
                    command->execute();
                    delete command;
                }
            });

            actions[name] = action;
        }
    }

    QAction* getAction(const QString& actionName) const {
        return actions.value(actionName);
    }

private:
    QMap<QString, QAction*> actions;
};
