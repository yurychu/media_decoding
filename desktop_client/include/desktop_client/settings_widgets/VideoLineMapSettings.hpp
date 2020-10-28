#pragma once

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/blocks_for_settings/CheckBox.hpp>
#include <desktop_client/blocks_for_settings/LabeledIntEditLine.hpp>


class VideoLineMapSettings : public SaveableJSONWidget
{
    Q_OBJECT
public:
    explicit VideoLineMapSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~VideoLineMapSettings() override = default;

    static const QString& getKeyName();

public:
    QJsonObject stateToJson() const;

private slots:
    void updateStateToSaver();


public:
    QCheckBox* m_checkBox;
    LabeledIntEditLine * m_field1;
    LabeledIntEditLine * m_field2;

};
