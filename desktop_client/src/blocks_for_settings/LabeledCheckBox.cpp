
#include <desktop_client/blocks_for_settings/LabeledCheckBox.hpp>

#include <QLayout>


LabeledCheckBox::LabeledCheckBox(QWidget *parent)
        : QHBoxLayout{parent},
          m_checkBox{nullptr}
{
    m_checkBox = new QCheckBox {tr("&Enable: ")};
    m_checkBox->setCheckState(Qt::Unchecked);

    addWidget(m_checkBox);
}


bool LabeledCheckBox::isChecked() const
{
    return m_checkBox->isChecked();
}
