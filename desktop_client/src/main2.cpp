
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>



int main(int argc, char*argv[]) {

    QApplication dsk_client_app {argc, argv};

    auto window = new QWidget {};
    window->setWindowTitle("Enter Your Age");

    auto spin_box = new QSpinBox {};
    auto slider = new QSlider {Qt::Horizontal};
    spin_box->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(
            spin_box, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int))
    );
    QObject::connect(
            slider, SIGNAL(valueChanged(int)),
            spin_box, SLOT(setValue(int))
    );

    spin_box->setValue(30);

    auto layout = new QHBoxLayout {};
    layout->addWidget(spin_box);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();

    return dsk_client_app.exec();
}