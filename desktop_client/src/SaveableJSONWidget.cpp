
#include <desktop_client/SaveableJSONWidget.hpp>


/*
 * SaveableJSONWidget
 *
 */
SaveableJSONWidget::SaveableJSONWidget(StructureSettingsSaver* saver, QWidget* parent)
        : QWidget{parent}
{
    // to saver obj
    QObject::connect(this, SIGNAL(jsonObjectDone(const QString &, const QJsonObject&)),
                     saver, SLOT(onSettingsChanged(const QString &, const QJsonObject&)));

}

void SaveableJSONWidget::stateToSaver(const QString &keyStr, const QJsonObject &obj)
{
    emit jsonObjectDone(keyStr, obj);
}
