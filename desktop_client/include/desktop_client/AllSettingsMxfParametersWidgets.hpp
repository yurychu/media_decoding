#pragma once

#include <QWidget>
#include <QLabel>
#include <QCheckBox>

#include <desktop_client/StructureSettingsSaver.hpp>


class EnableCheckBox : public QWidget
{
public:
    explicit EnableCheckBox(QWidget* parent);
    ~EnableCheckBox() override = default;

    bool isChecked() const;

public:
    QCheckBox * m_checkBox;
};


/*
 * FormatVersionSettings
 */
class FormatVersionSettings : public QWidget
{
    Q_OBJECT
public:
    explicit FormatVersionSettings(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~FormatVersionSettings() override = default;

    static const QString& getKeyName();

private slots:
    void updateToObj();

signals:
    void settingsDone(const QString &keyStr, const QJsonObject& obj);

private:
    EnableCheckBox* enableCheckBox;

};
