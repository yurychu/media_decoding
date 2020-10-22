
#include <desktop_client/SettingsBlockWidget.hpp>

#include <QGroupBox>
#include <QLayout>

SettingsBlockWidget::SettingsBlockWidget(QWidget * parent)
    : QWidget{parent}
{
    setLayout(new QHBoxLayout{});
}

void SettingsBlockWidget::addSettingsTile(QWidget *widget, QString boxName)
{
    const auto box = new QGroupBox {boxName, this};
    widget->setParent(box);
    layout()->addWidget(box);
}
