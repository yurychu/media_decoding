#pragma once

#include <QLayout>
#include <QComboBox>
#include <QLabel>


class LabeledComboBox : public QHBoxLayout
{
public:
    explicit LabeledComboBox(QWidget* parent=nullptr);
    ~LabeledComboBox() override = default;

public:
    QComboBox * m_comboBox;
    QLabel * m_label;

};
