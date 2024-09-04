#pragma once
class IntParam : public BaseParam {
public:
    IntParam(const QString& paramName) : paramName(paramName), value(0) {}

    QString name() const override { return paramName; }
    int getValue() const { return value; }

    void setValueFromWidget(QWidget* widget) override {
        if (auto* spinBox = qobject_cast<QSpinBox*>(widget)) {
            value = spinBox->value();
        }
    }

    void bindToWidget(QWidget* widget) override {
        if (auto* spinBox = qobject_cast<QSpinBox*>(widget)) {
            spinBox->setValue(value);
        }
    }

private:
    QString paramName;
    int value;
};
