#pragma once

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/blocks_for_settings/CheckBox.hpp>
#include <desktop_client/blocks_for_settings/LabeledWidthHeight.hpp>
#include <desktop_client/blocks_for_settings/JSONObjState.hpp>


class ResolutionSettings : public SaveableJSONWidget
{
Q_OBJECT
public:
    explicit ResolutionSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~ResolutionSettings() override = default;

    static const QString& getKeyName();

private slots:
    void updateOnEnabled();

private:
    QCheckBox* enableCheckBox;

    JSONObjState m_json_obj_state;
};
