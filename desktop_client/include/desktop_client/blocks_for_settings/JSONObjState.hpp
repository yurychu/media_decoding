#pragma once


#include <QObject>
#include <QJsonObject>


class JSONObjState : public QObject
{
    Q_OBJECT
public:
    explicit JSONObjState(const QString& objName, QObject* parent=nullptr);
    ~JSONObjState() override = default;

signals:
    void jsonObjUpdated(const QString& keyStr, const QJsonObject& obj);

public slots:
    void updateObjState(const QJsonObject& obj);
    void updateObjOnKey(const QString& keyStr, const QJsonObject& obj);
    void callUpdatedForward(const QJsonObject& obj);

public:
    QJsonObject m_json_obj;
};
