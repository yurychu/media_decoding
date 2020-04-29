#include <desktop_client/ClientWindow.hpp>

#include <iostream>
#include <thread>

#include <ui_ClientInterface.h>
#include <QFileDialog>


md_ui::ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::ClientInterface),
    m_picked_file{}
{
    ui->setupUi(this);

    QObject::connect(
            ui->actionOpen, &QAction::triggered,
            this, &ClientWindow::open
    );
}

md_ui::ClientWindow::~ClientWindow()
{
    delete ui;
}

void md_ui::ClientWindow::open()
{
    m_picked_file = QFileDialog::getOpenFileName(this, "Open:").toStdString();
    std::cout << "Picked: " << m_picked_file << std::endl;
    ui->textBrowser->setText(
            QString::fromStdString(m_picked_file)
    );

}
