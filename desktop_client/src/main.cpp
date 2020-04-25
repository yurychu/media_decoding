

#include <QApplication>

#include <desktop_client/ClientWindow.hpp>

int main(int argc, char*argv[]) {

    QApplication dsk_client_app{argc, argv};
    md_ui::ClientWindow client_window {};
    client_window.show();

    return QApplication::exec();
}