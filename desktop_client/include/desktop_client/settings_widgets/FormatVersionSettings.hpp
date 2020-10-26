#pragma once

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/LabeledCheckBox.hpp>
#include <desktop_client/LabeledComboBox.hpp>

/*
 * FormatVersionSettings
 */
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
    LabeledCheckBox* enableCheckBox;
    LabeledComboBox* labeledComboBox;

};
