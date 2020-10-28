#pragma once

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>

#include <desktop_client/SelectFilesWidget.hpp>
#include <desktop_client/SettingsBlockWidget.hpp>

class MxfSpecMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MxfSpecMainWindow();
    ~MxfSpecMainWindow() override = default;

private:
    void createMenus();
    void createStatusBar();
    void createCentralWidget();
    void completeSettingsBlock();

    SelectFilesWidget *getSelectFilesWidget();
    SettingsBlockWidget *getSettingsBlockWidget();

private:
    SettingsBlockWidget* settingsBlockWidget;
    SelectFilesWidget* selectFilesWidget;

    QTextBrowser* jsonTextBrowser;
    QTextBrowser* resultTextBrowser;

    QPushButton* startButton;

};
