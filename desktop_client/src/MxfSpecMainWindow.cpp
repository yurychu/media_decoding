
#include <desktop_client/MxfSpecMainWindow.hpp>

#include <QSplitter>
#include <QTextBrowser>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>

#include <iostream>

#include <desktop_client/SettingsBlockWidget.hpp>


MxfSpecMainWindow::MxfSpecMainWindow()
    : QMainWindow{},
    settingsBlockWidget{nullptr},
    selectFilesWidget{nullptr}
{
    createMenus();
    createStatusBar();
    createCentralWidget();

    setWindowTitle("Mxf spec parameters");
}


void MxfSpecMainWindow::createMenus()
{
    const auto fileMenu = menuBar()->addMenu(tr("&File"));
}


void MxfSpecMainWindow::createStatusBar()
{
    statusBar()->addWidget(new QLabel{"Status bar"});
}


void MxfSpecMainWindow::createCentralWidget()
{
    const auto mainSplitter = new QSplitter {Qt::Horizontal};
    const auto rightSplitter = new QSplitter { Qt::Vertical };

    const auto textBrowser = new QTextBrowser{};
    rightSplitter->addWidget(getSettingsBlockWidget()); // settings block
    rightSplitter->addWidget(textBrowser);  // results

    mainSplitter->addWidget(getSelectFilesWidget());
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(1, 1);

    QObject::connect(getSettingsBlockWidget(), SIGNAL(settingsUpdated(const QString&)),
                     textBrowser, SLOT(setPlainText(const QString&)));

    completeSettingsBlock();
    setCentralWidget(mainSplitter);
}


void MxfSpecMainWindow::completeSettingsBlock()
{
    const auto settingsBlockW = getSettingsBlockWidget();
    const auto all_settings_tiles = settingsBlockW->getAllSettingsTiles();

    for (const auto item : all_settings_tiles){
        settingsBlockW->addSettingsTile(item, item->objectName());
    }

}


SelectFilesWidget *MxfSpecMainWindow::getSelectFilesWidget()
{
    if (selectFilesWidget){
        return selectFilesWidget;
    }
    else {
        selectFilesWidget = new SelectFilesWidget {};
        return selectFilesWidget;
    }
}


SettingsBlockWidget *MxfSpecMainWindow::getSettingsBlockWidget()
{
    if (settingsBlockWidget){
        return settingsBlockWidget;
    }
    else {
        settingsBlockWidget = new SettingsBlockWidget {};
        return settingsBlockWidget;
    }
}
