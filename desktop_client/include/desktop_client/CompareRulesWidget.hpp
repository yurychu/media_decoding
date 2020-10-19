#pragma once

#include <QWidget>

#include <u_interfaces/ui_CompareRulesWidget.h>


class CompareRulesWidget : public QWidget, public Ui::CompareRulesWidget
{
    Q_OBJECT
public:
    explicit CompareRulesWidget(QWidget* parent = nullptr);
    ~CompareRulesWidget() override = default;

private:




};

