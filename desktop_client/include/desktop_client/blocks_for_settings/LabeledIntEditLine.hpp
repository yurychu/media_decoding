#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QString>

#include <desktop_client/blocks_for_settings/JSONObjState.hpp>


class LabeledIntEditLine : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledIntEditLine(const QString& labelText,
                                QWidget* parent=nullptr);
    ~LabeledIntEditLine() override = default;

public slots:
    void updateToObj();

public:
    QLabel * m_label;
    QLineEdit * m_lineEdit;

    JSONObjState m_json_obj_state;
};
