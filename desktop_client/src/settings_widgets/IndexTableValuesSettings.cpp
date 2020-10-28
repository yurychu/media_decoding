
#include <desktop_client/settings_widgets/IndexTableValuesSettings.hpp>

#include <vector>

#include <QLayout>



IndexTableValuesSettings::IndexTableValuesSettings(StructureSettingsSaver *saver, QWidget *parent)
        : SaveableJSONWidget{saver, parent},
        enableCheckBox{nullptr},
        sliceCount{nullptr},
        positionTableCount{nullptr},
        editUnitByteCount{nullptr},
        duration{nullptr}
{
    setObjectName(IndexTableValuesSettings::getKeyName());

    auto layout = new QVBoxLayout{this};

    enableCheckBox = makeUncheckedCheckBox(getEnableLiteral());
    layout->addWidget(enableCheckBox);

    std::vector<LabeledComparator*> elems;

    sliceCount = new LabeledComparator{"Slice count"};
    elems.emplace_back(sliceCount);

    positionTableCount = new LabeledComparator{"Position Table Count"};
    elems.emplace_back(positionTableCount);

    editUnitByteCount = new LabeledComparator{"Edit Unit Byte Count"};
    elems.emplace_back(editUnitByteCount);

    duration = new LabeledComparator{"Duration"};
    elems.emplace_back(duration);

    for (const auto elem : elems){
        layout->addWidget(elem);
        QObject::connect(elem, SIGNAL(somethingChanged()),
                         this, SLOT(updateStateToSaver()));
    }
    QObject::connect(enableCheckBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateStateToSaver()));

    updateStateToSaver();
}


QJsonObject IndexTableValuesSettings::stateToJson() const
{
    QJsonObject obj {};
    if (enableCheckBox->isChecked()){
        sliceCount->injectToObj(obj);
        positionTableCount->injectToObj(obj);
        editUnitByteCount->injectToObj(obj);
        duration->injectToObj(obj);
    }
    return obj;
}


void IndexTableValuesSettings::updateStateToSaver()
{
    const auto json_obj = stateToJson();
    stateToSaver(getKeyName(), json_obj);
}


const QString &IndexTableValuesSettings::getKeyName() {
    const static QString keyName {"IndexTableValues"};
    return keyName;
}

