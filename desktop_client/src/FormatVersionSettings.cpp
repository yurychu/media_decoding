
#include <desktop_client/FormatVersionSettings.hpp>


#include <QLayout>
#include <QComboBox>
#include <QLabel>

#include <iostream>


/*
 * FormatVersionSettings
 */
FormatVersionSettings::FormatVersionSettings(StructureSettingsSaver* saver, QWidget* parent)
        : SaveableJSONWidget{saver, parent},
          enableCheckBox{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{};

    enableCheckBox = new LabeledCheckBox{};
    labeledComboBox = new LabeledComboBox{};

    labeledComboBox->m_label->setText("&Format Version: ");
    labeledComboBox->m_comboBox->addItem("1.1");
    labeledComboBox->m_comboBox->addItem("1.2");
    labeledComboBox->m_comboBox->addItem("1.3");

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


const QString &FormatVersionSettings::getKeyName()
{
    const static QString keyName {"FormatVersion"};
    return keyName;
}


void FormatVersionSettings::updateToObj()
{
    QJsonObject obj {};

    if (enableCheckBox->isChecked()){
        const auto elem = labeledComboBox->m_comboBox->currentText();
        obj["ExpectedValue"] = elem;
    }

    stateToSaver(getKeyName(), obj);
}
