#pragma once

#include <QWidget>
#include <QLabel>
#include <QCheckBox>

#include <desktop_client/SaveableJSONWidget.hpp>
#include <desktop_client/EnableCheckBox.hpp>


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
    EnableCheckBox* enableCheckBox;

};
