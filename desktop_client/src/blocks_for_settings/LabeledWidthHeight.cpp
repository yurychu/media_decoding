
#include <desktop_client/blocks_for_settings/LabeledWidthHeight.hpp>


LabeledWidthHeight::LabeledWidthHeight(const QString& labelName, QWidget *parent)
    : QHBoxLayout{parent},
    m_checkBox{nullptr}
{
    m_checkBox = new QCheckBox{labelName};
    m_checkBox->setCheckState(Qt::Unchecked);

    // todo: add labeled int edit line


    addWidget(m_checkBox);
}
