
#include <desktop_client/ClientWindow.hpp>
#include <ui_ClientInterface.h>

md_ui::ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);
}

md_ui::ClientWindow::~ClientWindow()
{
    delete ui;
}
