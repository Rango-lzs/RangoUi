#pragma once
#include <QString>

class BaseParam {
public:
    virtual ~BaseParam() = default;
    virtual QString name() const = 0;
    virtual void setValueFromWidget(QWidget* widget) = 0;
    virtual void bindToWidget(QWidget* widget) = 0;
};
