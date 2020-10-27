
#include <desktop_client/blocks_for_settings/JSONObjState.hpp>


JSONObjState::JSONObjState(const QString& objName, QObject* parent)
    : QObject{parent}
{
    setObjectName(objName);
}


void JSONObjState::updateObjState(const QJsonObject &obj)
{
    m_json_obj = obj;
    emit jsonObjUpdated(objectName(), m_json_obj);
}


void JSONObjState::updateObjOnKey(const QString& keyStr, const QJsonObject& obj)
{
    if (obj.isEmpty()){
        if (m_json_obj.contains(keyStr)){
            m_json_obj.remove(keyStr);
        }
    }
    else {
        m_json_obj[keyStr] = obj;
    }

    emit jsonObjUpdated(objectName(), m_json_obj);
}


void JSONObjState::callUpdatedForward(const QJsonObject &obj)
{
    emit jsonObjUpdated(objectName(), obj);
}
