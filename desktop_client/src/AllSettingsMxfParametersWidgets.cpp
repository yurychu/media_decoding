
#include <desktop_client/AllSettingsMxfParametersWidgets.hpp>

#include <QLayout>

#include <iostream>


EnableCheckBox::EnableCheckBox(QWidget *parent)
    : QWidget(parent),
    m_checkBox{nullptr}
{
    m_checkBox = new QCheckBox {tr("&Enable: ")};
    m_checkBox->setCheckState(Qt::Unchecked);

    auto layout = new QHBoxLayout {};
    layout->addWidget(m_checkBox);

    setLayout(layout);
}


bool EnableCheckBox::isChecked() const
{
    return m_checkBox->isChecked();
}


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

