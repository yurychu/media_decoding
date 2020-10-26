
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
    std::cout << "On settings changed: key: " << keyStr.toStdString() << std::endl;
    m_json_obj[keyStr] = obj;
    QJsonDocument doc {m_json_obj};
    const QString json_str { doc.toJson() };

    emit jsonObjNewState(json_str);
}
