#include "Window.hpp"

#include <QApplication>


md_ui::Window::Window(QWidget *parent)
    : QWidget(parent),
    m_button{nullptr},
    m_counter{0}
{
    setFixedSize(400, 700);

    m_button = new QPushButton {"Test button", this};
    m_button->setGeometry(50, 50, 200, 100);
    m_button->setCheckable(true);

    QObject::connect(
            m_button, SIGNAL( clicked(bool) ),
            this, SLOT( slotButtonCliked(bool) )
    );


    QObject::connect(
            this, SIGNAL (counterReached()),
            QApplication::instance(), SLOT(quit())
    );

}


void md_ui::Window::slotButtonCliked(bool checked)
{
    if (checked){
        m_button->setText("Checked!");
    }
    else {
        m_button->setText("Hello my friend!");
    }
    ++m_counter;
    if (m_counter >= 10){
        emit counterReached();
    }

}
