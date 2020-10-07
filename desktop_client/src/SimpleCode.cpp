
#include <desktop_client/SimpleCode.hpp>

#include <QApplication>
#include <QLabel>

int run_simple_code_1(int argc, char * argv[])
{
    QApplication app{argc, argv};
    QLabel * label = new QLabel{"hello!!!"};
    label->show(); // all widgets before is invisible

    return app.exec();
}

#include <QPushButton>
int run_simple_code_2(int argc, char **argv)
{
    QApplication app { argc, argv };

    QPushButton * button = new QPushButton {"Press to quit"};

    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    button->show();


    return app.exec();
}

