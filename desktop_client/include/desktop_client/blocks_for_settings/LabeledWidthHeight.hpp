#pragma once

#include <QLayout>
#include <QCheckBox>
#include <QString>


class LabeledWidthHeight : public QHBoxLayout
{
public:
    explicit LabeledWidthHeight(const QString &labelName=QString{}, QWidget* parent=nullptr);
    ~LabeledWidthHeight() override = default;

public:
    QCheckBox* m_checkBox;

};
