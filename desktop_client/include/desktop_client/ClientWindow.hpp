#pragma once

#include <string>

#include <QMainWindow>

#include <u_interfaces/ui_ClientInterface.h>

namespace md_ui
{

    class ClientWindow : public QMainWindow
    {
        Q_OBJECT
    private:
        Ui::ClientInterface *ui;
        std::string m_picked_file;

    public:
        explicit ClientWindow(QWidget *parent = nullptr);
        ~ClientWindow() override;

    private slots:
        void open();


    };


}
