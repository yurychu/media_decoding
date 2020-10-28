#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QJsonObject>


class LabeledIntEditLine : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledIntEditLine(const QString& labelText,
                                QWidget* parent=nullptr);
    ~LabeledIntEditLine() override = default;

public:
    /*
    * only { "ExpectedValue": 0 }
    */
    QJsonObject stateToJson() const;

    /*
    * key name of json object
    */
    QString keyName() const;

    /*
     * add to obj with key { key: { "ExpectedValue": 0 } }
     */
    void injectToObj(QJsonObject& obj) const;

signals:
    void somethingChanged();


public:
    QLabel * m_label;
    QLineEdit * m_lineEdit;

};
