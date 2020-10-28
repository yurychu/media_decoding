#pragma once

#include <QWidget>
#include <QString>
#include <QJsonObject>
#include <QComboBox>
#include <QLineEdit>

#include <desktop_client/blocks_for_settings/CheckBox.hpp>


class LabeledComparator : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledComparator(const QString &labelName, QWidget* parent=nullptr);
    ~LabeledComparator() override = default;

public:
    QJsonObject stateToJson() const;
    QString keyName() const;
    void injectToObj(QJsonObject &obj) const;

signals:
    void somethingChanged();

public:
    QCheckBox* m_checkBox;
    QComboBox * m_comboBox;
    QLineEdit * m_lineEdit;

};

