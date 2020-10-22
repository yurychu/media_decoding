
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

    createSettingsBlock();

    rightSplitter->addWidget(getSettingsBlockWidget()); // settings block
    rightSplitter->addWidget(new QTextBrowser{});  // results

    mainSplitter->addWidget(getSelectFilesWidget());
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(1, 1);

    setCentralWidget(mainSplitter);
}


void MxfSpecMainWindow::createSettingsBlock()
{
    const auto settingsBlockW = getSettingsBlockWidget();

    const auto some1_widget = new QWidget {};

    settingsBlockW->addSettingsTile(some1_widget, "Some 1");
    settingsBlockW->addSettingsTile(new QWidget{}, "Some 2");

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
