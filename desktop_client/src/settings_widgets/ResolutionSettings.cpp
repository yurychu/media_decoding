
#include <desktop_client/settings_widgets/ResolutionSettings.hpp>

#include <vector>

#include <QLayout>


ResolutionSettings::ResolutionSettings(StructureSettingsSaver* saver, QWidget* parent)
        : SaveableJSONWidget{saver, parent},
        m_json_obj_state{getKeyName()},
        enableCheckBox{nullptr}
{
    setObjectName(getKeyName());

    auto layout = new QVBoxLayout{this};

    enableCheckBox = makeUncheckedCheckBox(getEnableLiteral());
    layout->addWidget(enableCheckBox);

    std::vector<LabeledWidthHeight*> elems;

    const auto storedResolutionWH = new LabeledWidthHeight{"Stored Resolution"};
    elems.emplace_back(storedResolutionWH);

    const auto displayResolutionWH = new LabeledWidthHeight{"Display Resolution"};
    elems.emplace_back(displayResolutionWH);

    const auto sampledResolutionWH = new LabeledWidthHeight{"Sampled Resolution"};
    elems.emplace_back(sampledResolutionWH);

    for (const auto elem : elems){
        layout->addWidget(elem);
        QObject::connect(&elem->m_json_obj_state, SIGNAL(jsonObjUpdated(const QString&, const QJsonObject&)),
                         &m_json_obj_state, SLOT(updateObjOnKey(const QString&, const QJsonObject&)));
    }

    // checked update
    QObject::connect(enableCheckBox, SIGNAL(stateChanged(int)),
                     this, SLOT(updateOnEnabled()));

    QObject::connect(&m_json_obj_state, SIGNAL(jsonObjUpdated(const QString&, const QJsonObject&)),
                     this, SLOT(updateOnEnabled()));

    updateOnEnabled();
}


const QString & ResolutionSettings::getKeyName()
{
    const static QString keyName {"Resolution"};
    return keyName;
}


void ResolutionSettings::updateOnEnabled()
{
    QJsonObject obj {};

    if (enableCheckBox->isChecked()){
        obj = m_json_obj_state.m_json_obj;
    }

    stateToSaver(getKeyName(), obj);
}
