#pragma once

#include <QObject>
#include <QJsonObject>


class StructureSettingsSaver : public QObject
{
    Q_OBJECT
public:
    explicit StructureSettingsSaver(QObject* parent = nullptr);
    ~StructureSettingsSaver() override = default;

    const QJsonObject& getJsonObj() const;

public slots:
    void onSettingsChanged(const QString &keyStr,
                           const QJsonObject& obj);
signals:
    void jsonObjNewState(const QString & str);

private:
    QJsonObject m_json_obj;

};
