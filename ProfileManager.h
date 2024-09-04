#pragma once

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QMap>

class ProfileManager {
public:
    ProfileManager() = default;

    bool loadProfile(const QString& filePath) {
        // 加载并解析XML文件
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }

        QDomDocument doc;
        if (!doc.setContent(&file)) {
            file.close();
            return false;
        }
        file.close();
        profiles[filePath] = doc;
        return true;
    }

    QDomDocument getProfile(const QString& filePath) const {
        return profiles.value(filePath);
    }

private:
    QMap<QString, QDomDocument> profiles;
};
