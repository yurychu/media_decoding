#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLabel>


class LabeledComboBox : public QWidget
{
public:
    explicit LabeledComboBox(QWidget* parent=nullptr);
    ~LabeledComboBox() override = default;

public:
    QComboBox * m_comboBox;
    QLabel * m_label;

};
