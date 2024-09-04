#pragma once

class ParamBinder {
public:
    void bindParamToWidget(const BaseParamPtr& param, QWidget* widget) {
        param->bindToWidget(widget);
        widgetMap[param->name()] = widget;
        paramMap[param->name()] = param;
    }

    void collectParamValues() {
        for (auto& param : paramMap) {
            if (auto* widget = widgetMap.value(param->name())) {
                param->setValueFromWidget(widget);
            }
        }
    }

    BaseParamPtr getParam(const QString& name) const {
        return paramMap.value(name);
    }

private:
    QMap<QString, QWidget*> widgetMap;
    QMap<QString, BaseParamPtr> paramMap;
};
