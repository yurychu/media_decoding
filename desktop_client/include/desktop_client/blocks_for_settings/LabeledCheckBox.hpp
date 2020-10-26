#pragma once

#include <QLayout>
#include <QCheckBox>


class LabeledCheckBox : public QHBoxLayout
{
public:
    explicit LabeledCheckBox(QWidget* parent=nullptr);
    ~LabeledCheckBox() override = default;

    bool isChecked() const;

public:
    QCheckBox * m_checkBox;
};

