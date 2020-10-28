
#include <desktop_client/MxfSpecMainWindow.hpp>

#include <QSplitter>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QString>

#include <iostream>
#include <sstream>

#include <desktop_client/SettingsBlockWidget.hpp>


MxfSpecMainWindow::MxfSpecMainWindow()
    : QMainWindow{},
    settingsBlockWidget{nullptr},
    selectFilesWidget{nullptr},
    jsonTextBrowser{nullptr},
    resultTextBrowser{nullptr}
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

    rightSplitter->addWidget(getSettingsBlockWidget()); // settings block

    const auto browseSplitter = new QSplitter{ Qt::Horizontal };

    jsonTextBrowser = new QTextBrowser{};
    browseSplitter->addWidget(jsonTextBrowser);  // compiled json from settings block

    resultTextBrowser = new QTextBrowser{};
    browseSplitter->addWidget(resultTextBrowser);  // result testing browser

    rightSplitter->addWidget(browseSplitter);

    startButton = new QPushButton("Start!");
    rightSplitter->addWidget(startButton);

    mainSplitter->addWidget(getSelectFilesWidget());
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(1, 1);

    QObject::connect(getSettingsBlockWidget(), SIGNAL(settingsUpdated(const QString&)),
                     jsonTextBrowser, SLOT(setPlainText(const QString&)));

    QObject::connect(startButton, SIGNAL(clicked()),
                     this, SLOT(makeCheckFiles()));

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

void MxfSpecMainWindow::makeCheckFiles()
{
    QStringList files = getSelectFilesWidget()->getAllPaths();
    if (files.empty()){
        resultTextBrowser->setText(tr("No selected files for check"));
    }
    else {
        resultTextBrowser->clear();
    }

}
