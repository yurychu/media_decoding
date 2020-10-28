
#include <desktop_client/settings_widgets/ResolutionSettings.hpp>

#include <vector>

#include <QLayout>


ResolutionSettings::ResolutionSettings(StructureSettingsSaver* saver, QWidget* parent)
        : SaveableJSONWidget{saver, parent},
        enableCheckBox{nullptr},
        storedResolutionWH{nullptr},
        displayResolutionWH{nullptr},
        sampledResolutionWH{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{this};

    enableCheckBox = makeUncheckedCheckBox(getEnableLiteral());
    layout->addWidget(enableCheckBox);

    std::vector<LabeledWidthHeight*> elems;

    storedResolutionWH = new LabeledWidthHeight{"Stored Resolution"};
    elems.emplace_back(storedResolutionWH);

    displayResolutionWH = new LabeledWidthHeight{"Display Resolution"};
    elems.emplace_back(displayResolutionWH);

    sampledResolutionWH = new LabeledWidthHeight{"Sampled Resolution"};
    elems.emplace_back(sampledResolutionWH);

    for (const auto elem : elems){
        layout->addWidget(elem);
        QObject::connect(elem, SIGNAL(somethingChanged()),
                         this, SLOT(updateStateToSaver()));
    }
    QObject::connect(enableCheckBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateStateToSaver()));

    updateStateToSaver();
}


const QString & ResolutionSettings::getKeyName()
{
    const static QString keyName {"Resolution"};
    return keyName;
}


QJsonObject ResolutionSettings::stateToJson() const
{
    QJsonObject obj {};
    if (enableCheckBox->isChecked()){
        storedResolutionWH->injectToObj(obj);
        displayResolutionWH->injectToObj(obj);
        sampledResolutionWH->injectToObj(obj);
    }
    return obj;
}


void ResolutionSettings::updateStateToSaver()
{
    const auto json_obj = stateToJson();
    stateToSaver(getKeyName(), json_obj);
}
