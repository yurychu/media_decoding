
#include <desktop_client/SaveableJSONWidget.hpp>


/*
 * SaveableJSONWidget
 *
 */
SaveableJSONWidget::SaveableJSONWidget(StructureSettingsSaver* saver, QWidget* parent)
        : QWidget{parent},
        m_saver{saver}
{

}

void SaveableJSONWidget::stateToSaver(const QString &keyStr, const QJsonObject &obj)
{
    m_saver->onSettingsChanged(keyStr, obj);
}
