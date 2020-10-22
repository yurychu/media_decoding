
#include <desktop_client/MxfSpecMainWindow.hpp>

#include <QSplitter>
#include <QTextBrowser>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>

#include <iostream>


MxfSpecMainWindow::MxfSpecMainWindow()
    : QMainWindow{}
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
    statusBar()->addWidget(new QLabel{"Stat"});
}


void MxfSpecMainWindow::createCentralWidget()
{
    const auto mainSplitter = new QSplitter {Qt::Horizontal};

    selectFilesWidget = new SelectFilesWidget{};

    const auto rightSplitter = new QSplitter { Qt::Vertical };

//    const auto settingsBlockWidget = new SettingsBlockWidget{};

//    rightSplitter->addWidget(settingsBlockWidget); // settings block
    rightSplitter->addWidget(new QTextBrowser{});
    rightSplitter->addWidget(new QTextBrowser{});  // results

    mainSplitter->addWidget(selectFilesWidget);
    mainSplitter->addWidget(rightSplitter);

    setCentralWidget(mainSplitter);
}
