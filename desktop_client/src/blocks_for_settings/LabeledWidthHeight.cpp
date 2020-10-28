
#include <desktop_client/blocks_for_settings/LabeledWidthHeight.hpp>

#include <QLayout>

#include <desktop_client/blocks_for_settings/CheckBox.hpp>


LabeledWidthHeight::LabeledWidthHeight(const QString& labelName, QWidget *parent)
    : QWidget{parent},
    m_checkBox{nullptr},
    m_width{nullptr},
    m_height{nullptr}
{
    const auto layout = new QHBoxLayout{this};
    m_checkBox = makeUncheckedCheckBox(labelName);
    layout->addWidget(m_checkBox);

    m_width = new LabeledIntEditLine{"W"};
    m_height = new LabeledIntEditLine{"H"};

    layout->addWidget(m_width);
    layout->addWidget(m_height);

    QObject::connect(m_checkBox, SIGNAL(stateChanged(int)),
                     this, SIGNAL(somethingChanged()));

    QObject::connect(m_width, SIGNAL(somethingChanged()),
                     this, SIGNAL(somethingChanged()));

    QObject::connect(m_height, SIGNAL(somethingChanged()),
                     this, SIGNAL(somethingChanged()));

}


QJsonObject LabeledWidthHeight::stateToJson() const
{
    QJsonObject obj {};
    if (m_checkBox->isChecked()){
        m_width->injectToObj(obj);
        m_height->injectToObj(obj);
    }
    return obj;
}


QString LabeledWidthHeight::keyName() const {
    return m_checkBox->text();
}


void LabeledWidthHeight::injectToObj(QJsonObject &obj) const
{
    const auto state_json = stateToJson();
    if (!state_json.empty()){
        obj[keyName()] = state_json;
    }
}

