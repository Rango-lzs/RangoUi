#pragma once

class AsAlnHandleCommand : public ICommand {
public:
    AsAlnHandleCommand() {
        params.append(std::make_shared<IntParam>("handleSize"));
        params.append(std::make_shared<DoubleParam>("tolerance"));
        params.append(std::make_shared<StringParam>("constraintName"));
    }

    void execute() override {
        QDialog form;
        form.setWindowTitle("Assembly Handle");

        QFormLayout layout(&form);
        ParamBinder binder;

        for (const auto& param : params) {
            QWidget* widget = createWidgetForParam(param);
            layout.addRow(param->name(), widget);
            binder.bindParamToWidget(param, widget);
        }

        QPushButton okButton("OK");
        layout.addWidget(&okButton);
        QObject::connect(&okButton, &QPushButton::clicked, &form, &QDialog::accept);

        if (form.exec() == QDialog::Accepted) {
            binder.collectParamValues();
            int handleSize = std::static_pointer_cast<IntParam>(binder.getParam("handleSize"))->getValue();
            double tolerance = std::static_pointer_cast<DoubleParam>(binder.getParam("tolerance"))->getValue();
            QString constraintName = std::static_pointer_cast<StringParam>(binder.getParam("constraintName"))->getValue();

            handleAssembly(handleSize, tolerance, constraintName);
        }
    }

private:
    QList<BaseParamPtr> params;

    QWidget* createWidgetForParam(const BaseParamPtr& param) {
        if (std::dynamic_pointer_cast<IntParam>(param)) {
            return new QSpinBox();
        } else if (std::dynamic_pointer_cast<DoubleParam>(param)) {
            return new QDoubleSpinBox();
        } else if (std::dynamic_pointer_cast<StringParam>(param)) {
            return new QLineEdit();
        }
        return nullptr;
    }

    void handleAssembly(int handleSize, double tolerance, const QString& constraintName) {
        // 具体的处理逻辑
    }

    static CommandRegister<AsAlnHandleCommand> reg;
};

CommandRegister<AsAlnHandleCommand> AsAlnHandleCommand::reg("!AsAlnHandle");
