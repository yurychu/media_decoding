
#include <desktop_client/blocks_for_settings/LabeledComboBox.hpp>

#include <QLayout>


LabeledComboBox::LabeledComboBox(QWidget *parent)
    : QWidget{parent},
    m_comboBox{nullptr},
    m_label{nullptr}
{
    const auto layout = new QHBoxLayout{this};
    m_comboBox = new QComboBox{};
    m_label = new QLabel{};
    m_label->setBuddy(m_comboBox);

    layout->addWidget(m_label);
    layout->addWidget(m_comboBox);
}

