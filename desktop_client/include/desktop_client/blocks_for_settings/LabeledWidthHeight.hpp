#pragma once

#include <QCheckBox>
#include <QString>

#include <desktop_client/blocks_for_settings/LabeledIntEditLine.hpp>
#include <desktop_client/blocks_for_settings/JSONObjState.hpp>


class LabeledWidthHeight : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledWidthHeight(const QString &labelName, QWidget* parent=nullptr);
    ~LabeledWidthHeight() override = default;

private slots:
    void checkEnabled();

signals:
    void disabled();

public:
    QCheckBox* m_checkBox;
    LabeledIntEditLine *m_width;
    LabeledIntEditLine *m_height;

    JSONObjState m_json_obj_state;

};
