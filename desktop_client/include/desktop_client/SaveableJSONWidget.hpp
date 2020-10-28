#pragma once

#include <QWidget>

#include <desktop_client/StructureSettingsSaver.hpp>


class SaveableJSONWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SaveableJSONWidget(StructureSettingsSaver* saver, QWidget* parent=nullptr);
    ~SaveableJSONWidget() override = default;

protected:
    void stateToSaver(const QString &keyStr, const QJsonObject& obj);

private:
    StructureSettingsSaver* m_saver;

};
