
#include <desktop_client/StructureSettingsSaver.hpp>

#include <iostream>

#include <QJsonDocument>


StructureSettingsSaver::StructureSettingsSaver(QObject* parent)
    : QObject{parent},
    m_json_obj{}
{

}


void StructureSettingsSaver::onSettingsChanged(const QString &keyStr, const QJsonObject &obj)
{
    if (obj.isEmpty()){
        m_json_obj.remove(keyStr);
    }
    else {
        m_json_obj[keyStr] = obj;
    }

    QJsonDocument doc {m_json_obj};
    const QString json_str { doc.toJson() };

    emit jsonObjNewState(json_str);
}
