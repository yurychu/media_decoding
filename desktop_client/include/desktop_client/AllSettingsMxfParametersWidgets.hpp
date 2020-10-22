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


class SaveableJSONWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SaveableJSONWidget(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~SaveableJSONWidget() override = default;

protected:
    void stateToSaver(const QString &keyStr, const QJsonObject& obj);

signals:
    void jsonObjectDone(const QString &keyStr, const QJsonObject& obj);

};


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
