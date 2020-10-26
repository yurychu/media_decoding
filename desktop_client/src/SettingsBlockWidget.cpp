
#include <desktop_client/SettingsBlockWidget.hpp>

#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>

#include <desktop_client/AllSettingsMxfParametersWidgets.hpp>


SettingsBlockWidget::SettingsBlockWidget(QWidget * parent)
    : QWidget{parent},
    saver{nullptr}
{
    setLayout(new QHBoxLayout{});
    saver = new StructureSettingsSaver {this};

    QObject::connect(saver, SIGNAL(jsonObjNewState(const QString&)),
                     this, SIGNAL(settingsUpdated(const QString&)));
}


void SettingsBlockWidget::addSettingsTile(QWidget *widget, QString boxName)
{
    auto box_layout = new QVBoxLayout{};
    box_layout->setSpacing(0);
    box_layout->setContentsMargins(0, 0, 0, 0);
    box_layout->addWidget(widget);

    const auto box = new QGroupBox {boxName};
    box->setLayout(box_layout);
    layout()->addWidget(box);
}


std::vector<QWidget *> SettingsBlockWidget::getAllSettingsTiles() const
{
    std::vector<QWidget *> result;

    auto elem = new FormatVersionSettings {saver};
    result.emplace_back(elem);

    return result;
}
