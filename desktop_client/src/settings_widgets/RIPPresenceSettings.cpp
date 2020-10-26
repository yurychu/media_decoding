
#include <desktop_client/settings_widgets/RIPPresenceSettings.hpp>




#include <QLayout>
#include <QComboBox>
#include <QLabel>


RIPPresenceSettings::RIPPresenceSettings(StructureSettingsSaver* saver, QWidget* parent)
        : SaveableJSONWidget{saver, parent},
          enableCheckBox{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{};

    enableCheckBox = new LabeledCheckBox{};
    labeledComboBox = new LabeledComboBox{};

    labeledComboBox->m_label->setText("&RIP Presence: ");
    labeledComboBox->m_comboBox->addItem("True");
    labeledComboBox->m_comboBox->addItem("False");

    layout->addLayout(enableCheckBox);
    layout->addLayout(labeledComboBox);

    setLayout(layout);

    // checked update
    QObject::connect(enableCheckBox->m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateToObj()));

    QObject::connect(labeledComboBox->m_comboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updateToObj()));

    updateToObj();
}


const QString &RIPPresenceSettings::getKeyName()
{
    const static QString keyName {"RIPPresence"};
    return keyName;
}


void RIPPresenceSettings::updateToObj()
{
    QJsonObject obj {};

    if (enableCheckBox->isChecked()){
        const auto idx = labeledComboBox->m_comboBox->currentIndex();
        obj["ExpectedValue"] = (idx == 0);
    }

    stateToSaver(getKeyName(), obj);
}
