#pragma once

#include <QMainWindow>

#include <desktop_client/SelectFilesWidget.hpp>


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

private:
    SelectFilesWidget *selectFilesWidget;

};
