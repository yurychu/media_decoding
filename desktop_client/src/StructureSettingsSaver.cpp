
#include <desktop_client/StructureSettingsSaver.hpp>

#include <iostream>


StructureSettingsSaver::StructureSettingsSaver(QObject* parent)
    : QObject{parent}
{

}


void StructureSettingsSaver::onSettingsChanged(const QString &keyStr, const QJsonObject &obj)
{
    std::cout << "On settings changed: key: " << keyStr.toStdString() << std::endl;
}
