
#include <desktop_client/blocks_for_settings/LabeledWidthHeight.hpp>

#include <QLayout>

#include <desktop_client/blocks_for_settings/CheckBox.hpp>


LabeledWidthHeight::LabeledWidthHeight(const QString& labelName, QWidget *parent)
    : QWidget{parent},
    m_json_obj_state{labelName},
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

    QObject::connect(&m_width->m_json_obj_state, SIGNAL(jsonObjUpdated(const QString &, const QJsonObject &)),
                     &m_json_obj_state, SLOT(updateObjOnKey(const QString&, const QJsonObject&)));

    QObject::connect(&m_height->m_json_obj_state, SIGNAL(jsonObjUpdated(const QString &, const QJsonObject &)),
                     &m_json_obj_state, SLOT(updateObjOnKey(const QString&, const QJsonObject&)));

    m_width->updateToObj();
    m_height->updateToObj();

    QObject::connect(m_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(checkEnabled()));

    checkEnabled();
}


void LabeledWidthHeight::checkEnabled()
{
    if (!m_checkBox->isChecked()){
        m_json_obj_state.callUpdatedForward({});
    }
}
