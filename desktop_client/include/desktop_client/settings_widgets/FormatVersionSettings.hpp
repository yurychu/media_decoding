#pragma once

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/blocks_for_settings/CheckBox.hpp>
#include <desktop_client/blocks_for_settings/LabeledComboBox.hpp>


class FormatVersionSettings : public SaveableJSONWidget
{
Q_OBJECT
public:
    explicit FormatVersionSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~FormatVersionSettings() override = default;

    static const QString& getKeyName();

private slots:
    void updateToObj();

private:
    QCheckBox* enableCheckBox;
    LabeledComboBox* labeledComboBox;

};
