
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


#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

int run_simple_code_3(int argc, char **argv)
{
    QApplication app{argc, argv};

    QWidget * window = new QWidget{};
    window->setWindowTitle("Your age");

    QSpinBox * spin_box = new QSpinBox {};
    QSlider * slider = new QSlider{Qt::Horizontal};

    spin_box->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(spin_box, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spin_box, SLOT(setValue(int)));

    spin_box->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout {};  // Менеджер компоновки элементов, не является виджетом.
    layout->addWidget(spin_box);
    layout->addWidget(slider);
    window->setLayout(layout);  // За кулисами делает виджеты в менеджере компоновки дочерними к окну.

    window->show();

    return app.exec();
}

