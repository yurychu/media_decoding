#include <QApplication>

#include <desktop_client/MxfSpecificParameters.hpp>


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    MxfSpecificParameters parameters;
    parameters.show();

    return app.exec();

}
