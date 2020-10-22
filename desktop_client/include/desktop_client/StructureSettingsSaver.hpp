#pragma once

#include <QObject>
#include <QJsonObject>


class StructureSettingsSaver : public QObject
{
    Q_OBJECT
public:
    explicit StructureSettingsSaver(QObject* parent = nullptr);
    ~StructureSettingsSaver() override = default;

public slots:
    void onSettingsChanged(const QString &keyStr,
                           const QJsonObject& obj);

};
