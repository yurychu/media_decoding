
#include <desktop_client/blocks_for_settings/LabeledComparator.hpp>

#include <QLayout>


LabeledComparator::LabeledComparator(const QString &labelName, QWidget *parent)
    : QWidget{parent}
{
    const auto layout = new QHBoxLayout{this};

    m_checkBox = makeUncheckedCheckBox(labelName);

    m_comboBox = new QComboBox{};
    m_comboBox->addItem("=");
    m_comboBox->addItem("!=");
    m_comboBox->addItem(">");
    m_comboBox->addItem(">=");
    m_comboBox->addItem("<");
    m_comboBox->addItem("<=");

    QRegExp regExp {"^[0-9]+$"};
    auto regExpValidator = new QRegExpValidator{regExp, this};
    m_lineEdit = new QLineEdit{};
    m_lineEdit->setValidator(regExpValidator);
    m_lineEdit->setText("0");

    layout->addWidget(m_checkBox);
    layout->addWidget(m_comboBox);
    layout->addWidget(m_lineEdit);

    QObject::connect(m_checkBox, SIGNAL(stateChanged(int)),
                     this, SIGNAL(somethingChanged()));

    QObject::connect(m_comboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(somethingChanged()));

    QObject::connect(m_lineEdit, SIGNAL(textChanged(const QString &)),
                     this, SIGNAL(somethingChanged()));

}

/*
 *  "CompareRules": {
 *    "ComparatorMain": {
 *      "Operator": ">",
 *      "Value": 100
 *    }
 *  }
 */
QJsonObject LabeledComparator::stateToJson() const
{
    QJsonObject obj {};

    if (m_checkBox->isChecked()) {
        QJsonObject compare_rules {};
        QJsonObject comparator_main {};

        int res = 0;
        const auto text_line = m_lineEdit->text();
        if (!text_line.isEmpty()) {
            res = text_line.toInt();
        }
        comparator_main["Value"] = res;

        const auto comp_op = m_comboBox->currentText();
        comparator_main["Operator"] = comp_op;

        compare_rules["ComparatorMain"] = comparator_main;
        obj["CompareRules"] = compare_rules;
    }

    return obj;
}


QString LabeledComparator::keyName() const
{
    return m_checkBox->text();
}


void LabeledComparator::injectToObj(QJsonObject &obj) const
{
    obj[keyName()] = stateToJson();
}
