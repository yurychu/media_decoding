
#include <desktop_client/blocks_for_settings/LabeledComboBox.hpp>


LabeledComboBox::LabeledComboBox(QWidget *parent)
    : QHBoxLayout{parent},
    m_comboBox{nullptr},
    m_label{nullptr}
{
    m_comboBox = new QComboBox{};
    m_label = new QLabel{};

    addWidget(m_label);
    addWidget(m_comboBox);

    m_label->setBuddy(m_comboBox);
}
