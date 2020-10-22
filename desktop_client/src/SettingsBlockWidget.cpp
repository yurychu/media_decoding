
#include <desktop_client/SettingsBlockWidget.hpp>

#include <QGroupBox>
#include <QLayout>

#include <desktop_client/AllSettingsMxfParametersWidgets.hpp>


SettingsBlockWidget::SettingsBlockWidget(QWidget * parent)
    : QWidget{parent},
    saver{nullptr}
{
    setLayout(new QHBoxLayout{});
    saver = new StructureSettingsSaver {this};
}

void SettingsBlockWidget::addSettingsTile(QWidget *widget, QString boxName)
{
    const auto box = new QGroupBox {boxName, this};
    widget->setParent(box);
    layout()->addWidget(box);
}


std::vector<QWidget *> SettingsBlockWidget::getAllSettingsTiles()
{
    std::vector<QWidget *> result;

    auto elem = new FormatVersionSettings {saver};
    result.emplace_back(elem);

    return result;
}
