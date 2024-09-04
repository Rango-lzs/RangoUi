#pragma once

#include <QIcon>

class ResourcePool {
public:
    QIcon getIcon(const QString& name) const {
        // 根据名字获取图标
        return QIcon(name);
    }

    QString getHint(const QString& name) const {
        // 根据名字获取提示信息
        return QString("Hint for %1").arg(name);
    }
};
