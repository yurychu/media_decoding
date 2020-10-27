
#include <desktop_client/settings_widgets/ResolutionSettings.hpp>

#include <QLayout>


ResolutionSettings::ResolutionSettings(StructureSettingsSaver* saver, QWidget* parent)
        : SaveableJSONWidget{saver, parent},
          enableCheckBox{nullptr},
          storedResolutionWH{nullptr},
          displayResolutionWH{nullptr},
          sampledResolutionWH{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{};

    enableCheckBox = new LabeledCheckBox{};

    storedResolutionWH = new LabeledWidthHeight{"Stored Resolution"};
    displayResolutionWH = new LabeledWidthHeight{"Display Resolution"};
    sampledResolutionWH = new LabeledWidthHeight{"Sampled Resolution"};
//    labeledComboBox = new LabeledComboBox{};
//
//    labeledComboBox->m_label->setText("&Resolution: ");
//    labeledComboBox->m_comboBox->addItem("True");
//    labeledComboBox->m_comboBox->addItem("False");

    layout->addLayout(enableCheckBox);
    layout->addLayout(storedResolutionWH);
    layout->addLayout(displayResolutionWH);
    layout->addLayout(sampledResolutionWH);

    setLayout(layout);

    // checked update
    QObject::connect(enableCheckBox->m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateToObj()));

//    QObject::connect(labeledComboBox->m_comboBox, SIGNAL(currentIndexChanged(int)),
//                     this, SLOT(updateToObj()));

    updateToObj();
}


const QString & ResolutionSettings::getKeyName()
{
    const static QString keyName {"Resolution"};
    return keyName;
}


void ResolutionSettings::updateToObj()
{
    QJsonObject obj {};

    if (enableCheckBox->isChecked()){
//        const auto idx = labeledComboBox->m_comboBox->currentIndex();
//        obj["ExpectedValue"] = (idx == 0);
    }

    stateToSaver(getKeyName(), obj);
}
