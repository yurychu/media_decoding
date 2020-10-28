

#include <desktop_client/blocks_for_settings/LabeledIntEditLine.hpp>

#include <QLayout>
#include <QRegExp>
#include <QRegExpValidator>


LabeledIntEditLine::LabeledIntEditLine(const QString& labelText,
                                       QWidget *parent)
    : QWidget{parent},
    m_label{nullptr},
    m_lineEdit{nullptr}
{
    const auto layout = new QHBoxLayout{this};

    m_label = new QLabel{labelText};
    layout->addWidget(m_label);

    QRegExp regExp {"^[0-9]+$"};
    auto regExpValidator = new QRegExpValidator{regExp, this};
    m_lineEdit = new QLineEdit{};
    m_lineEdit->setValidator(regExpValidator);
    m_lineEdit->setText("0");
    layout->addWidget(m_lineEdit);

    QObject::connect(m_lineEdit, SIGNAL(textChanged(const QString &)),
                     this, SIGNAL(somethingChanged()));

}

/*
 * only { "ExpectedValue": 0 }
 */
QJsonObject LabeledIntEditLine::stateToJson() const
{
    QJsonObject obj {};
    int res = 0;
    const auto text_line = m_lineEdit->text();
    if (!text_line.isEmpty()){
        res = text_line.toInt();
    }
    obj["ExpectedValue"] = res;
    return obj;
}

/*
 * key name of json object
 */
QString LabeledIntEditLine::keyName() const
{
    return m_label->text();
}

void LabeledIntEditLine::injectToObj(QJsonObject &obj) const
{
    obj[keyName()] = stateToJson();
}
