

#include <desktop_client/blocks_for_settings/LabeledIntEditLine.hpp>

#include <QLayout>
#include <QRegExp>
#include <QRegExpValidator>


LabeledIntEditLine::LabeledIntEditLine(const QString& labelText,
                                       QWidget *parent)
    : QWidget{parent},
    m_json_obj_state{labelText},
    m_label{nullptr},
    m_lineEdit{nullptr}
{
    const auto layout = new QHBoxLayout{this};

    m_label = new QLabel{labelText};
    layout->addWidget(m_label);

    QRegExp regExp {"^[0-9]+$"};
    auto regExpValidator = new QRegExpValidator{regExp, this};
    m_lineEdit = new QLineEdit{};
    m_lineEdit->setValidator(regExpValidator);
    layout->addWidget(m_lineEdit);

    QObject::connect(m_lineEdit, SIGNAL(textChanged(const QString&)),
                     this, SLOT(updateToObj()));

    updateToObj();
}


void LabeledIntEditLine::updateToObj()
{
    QJsonObject obj {};
    int res = 0;
    const auto text_line = m_lineEdit->text();
    if (!text_line.isEmpty()){
        res = text_line.toInt();
    }
    obj["ExpectedValue"] = res;
    m_json_obj_state.updateObjState(obj);
}
