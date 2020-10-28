
#include <desktop_client/settings_widgets/VideoLineMapSettings.hpp>

#include <QLayout>


VideoLineMapSettings::VideoLineMapSettings(StructureSettingsSaver *saver, QWidget *parent)
    : SaveableJSONWidget(saver, parent),
    m_checkBox{nullptr},
    m_field1{nullptr},
    m_field2{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{this};

    m_checkBox = makeUncheckedCheckBox(getEnableLiteral());
    layout->addWidget(m_checkBox);

    m_field1 = new LabeledIntEditLine{"Field1"};
    m_field2 = new LabeledIntEditLine{"Field2"};

    layout->addWidget(m_field1);
    layout->addWidget(m_field2);

    QObject::connect(m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateStateToSaver()));

    QObject::connect(m_field1, SIGNAL(somethingChanged()),
                     this, SLOT(updateStateToSaver()));

    QObject::connect(m_field2, SIGNAL(somethingChanged()),
                     this, SLOT(updateStateToSaver()));

    updateStateToSaver();
}

const QString &VideoLineMapSettings::getKeyName() {
    const static QString keyName {"VideoLineMap"};
    return keyName;
}


void VideoLineMapSettings::updateStateToSaver()
{
    const auto json_obj = stateToJson();
    stateToSaver(getKeyName(), json_obj);
}


QJsonObject VideoLineMapSettings::stateToJson() const
{
    QJsonObject obj {};
    if (m_checkBox->isChecked()){
        m_field1->injectToObj(obj);
        m_field2->injectToObj(obj);
    }
    return obj;
}
