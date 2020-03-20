#include "Window.hpp"

md_ui::Window::Window(QWidget *parent)
    : QWidget(parent),
    m_button{nullptr}
{
    setFixedSize(400, 700);

    m_button = new QPushButton {"Test button", this};
    m_button->setGeometry(50, 50, 200, 100);
}
