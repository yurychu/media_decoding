#pragma once

#include <QWidget>

#include <vector>

#include <desktop_client/StructureSettingsSaver.hpp>


class SettingsBlockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsBlockWidget(QWidget * parent = nullptr);
    ~SettingsBlockWidget() override = default;

    void addSettingsTile(QWidget * widget, QString boxName);

    std::vector<QWidget*> getAllSettingsTiles() const;

signals:
    void settingsUpdated(const QString& str);

private:
    StructureSettingsSaver *saver;

};
