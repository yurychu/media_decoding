
#include <desktop_client/AllSettingsMxfParametersWidgets.hpp>

#include <QLayout>

#include <iostream>


/*
 * FormatVersionSettings
 */
FormatVersionSettings::FormatVersionSettings(StructureSettingsSaver* saver, QWidget* parent)
    : SaveableJSONWidget{saver, parent},
    enableCheckBox{nullptr}
{
    setObjectName(getKeyName());

    enableCheckBox = new EnableCheckBox{this};

    // checked update
    QObject::connect(enableCheckBox->m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateToObj()));

    updateToObj();
}


const QString &FormatVersionSettings::getKeyName()
{
    const static QString keyName {"FormatVersion"};
    return keyName;
}


void FormatVersionSettings::updateToObj()
{
    std::cout << "Update to obj call." << std::endl;
    QJsonObject obj {};
    stateToSaver(getKeyName(), obj);
}

