#pragma once

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/LabeledCheckBox.hpp>
#include <desktop_client/LabeledComboBox.hpp>


class RIPPresenceSettings : public SaveableJSONWidget
{
Q_OBJECT
public:
    explicit RIPPresenceSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~RIPPresenceSettings() override = default;

    static const QString& getKeyName();

private slots:
    void updateToObj();

private:
    LabeledCheckBox* enableCheckBox;
    LabeledComboBox* labeledComboBox;

};
