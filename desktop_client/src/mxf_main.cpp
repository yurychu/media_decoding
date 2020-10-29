#include <QApplication>

#include <desktop_client/MxfSpecMainWindow.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MxfSpecMainWindow mainWindow {};
    mainWindow.show();
    return app.exec();
}
