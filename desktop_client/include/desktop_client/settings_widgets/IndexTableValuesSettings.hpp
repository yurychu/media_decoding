#pragma once

#include <QJsonObject>

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/blocks_for_settings/CheckBox.hpp>
#include <desktop_client/blocks_for_settings/LabeledComparator.hpp>


class IndexTableValuesSettings : public SaveableJSONWidget
{
Q_OBJECT
public:
    explicit IndexTableValuesSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~IndexTableValuesSettings() override = default;

    static const QString& getKeyName();

public:
    QJsonObject stateToJson() const;

private slots:
    void updateStateToSaver();

private:
    QCheckBox* enableCheckBox;

    LabeledComparator* sliceCount;
    LabeledComparator* positionTableCount;
    LabeledComparator* editUnitByteCount;
    LabeledComparator* duration;

};
