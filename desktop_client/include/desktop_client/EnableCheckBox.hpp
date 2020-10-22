#pragma once

#include <QWidget>
#include <QCheckBox>


class EnableCheckBox : public QWidget
{
public:
    explicit EnableCheckBox(QWidget* parent);
    ~EnableCheckBox() override = default;

    bool isChecked() const;

public:
    QCheckBox * m_checkBox;
};

