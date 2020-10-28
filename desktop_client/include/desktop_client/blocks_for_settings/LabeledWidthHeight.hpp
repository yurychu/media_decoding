#pragma once

#include <QCheckBox>
#include <QString>
#include <QJsonObject>

#include <desktop_client/blocks_for_settings/LabeledIntEditLine.hpp>


class LabeledWidthHeight : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledWidthHeight(const QString &labelName, QWidget* parent=nullptr);
    ~LabeledWidthHeight() override = default;

public:
    QJsonObject stateToJson() const;
    QString keyName() const;
    void injectToObj(QJsonObject &obj) const;

signals:
    void somethingChanged();

public:
    QCheckBox* m_checkBox;
    LabeledIntEditLine *m_width;
    LabeledIntEditLine *m_height;

};
