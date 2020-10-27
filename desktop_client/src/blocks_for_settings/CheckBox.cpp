
#include <desktop_client/blocks_for_settings/CheckBox.hpp>


const QString &getEnableLiteral()
{
    const static QString lit{"Enable"};
    return lit;
}


QCheckBox* makeUncheckedCheckBox(const QString &text, QWidget*parent)
{
    auto checkBox = new QCheckBox{text, parent};
    checkBox->setCheckState(Qt::Unchecked);
    return checkBox;
}

