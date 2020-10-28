#pragma once

#include <QJsonObject>

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/blocks_for_settings/CheckBox.hpp>
#include <desktop_client/blocks_for_settings/LabeledWidthHeight.hpp>


class ResolutionSettings : public SaveableJSONWidget
{
Q_OBJECT
public:
    explicit ResolutionSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~ResolutionSettings() override = default;

    static const QString& getKeyName();

public:
    QJsonObject stateToJson() const;

private slots:
    void updateStateToSaver();

private:
    QCheckBox* enableCheckBox;

    LabeledWidthHeight* storedResolutionWH;
    LabeledWidthHeight* displayResolutionWH;
    LabeledWidthHeight* sampledResolutionWH;

};
