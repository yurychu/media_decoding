#pragma once

#include <QWidget>
#include <u_interfaces/ui_SpecificMxfParamters.h>




class MxfSpecificParameters : public QWidget, public Ui::MxfSpecificForm
{
    Q_OBJECT
public:
    MxfSpecificParameters();
    ~MxfSpecificParameters() override = default;

private slots:
    void open();

    void checkMxfFile();

};
