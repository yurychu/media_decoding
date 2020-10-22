
#include <desktop_client/AllSettingsMxfParametersWidgets.hpp>

#include <QLayout>


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
    : QWidget{parent}
{

}
