#pragma once

#include <QWidget>

#include <vector>


class SettingsBlockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsBlockWidget(QWidget * parent = nullptr);
    ~SettingsBlockWidget() override = default;

    void addSettingsTile(QWidget * widget, QString boxName);

    static std::vector<QWidget*> getAllSettingsTiles();

private:



};
