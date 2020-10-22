
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
 * FormatVersionSettings
 */
FormatVersionSettings::FormatVersionSettings(StructureSettingsSaver* saver, QWidget* parent)
    : QWidget{parent},
    enableCheckBox{nullptr}
{
    enableCheckBox = new EnableCheckBox{this};

    // to saver obj
    QObject::connect(this, SIGNAL(settingsDone(const QString &, const QJsonObject&)),
                     saver, SLOT(onSettingsChanged(const QString &, const QJsonObject&)));

    // checked
    QObject::connect(enableCheckBox->m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateToObj()));

    QJsonObject obj{};
    emit settingsDone(getKeyName(), obj);

}

const QString &FormatVersionSettings::getKeyName()
{
    const static QString keyName {"FormatVersion"};
    return keyName;
}

void FormatVersionSettings::updateToObj()
{
    std::cout << "Update to obj call." << std::endl;
    QJsonObject obj{};
    emit settingsDone(getKeyName(), obj);
}
