#pragma once

#include <QWidget>
#include <QPushButton>


namespace md_ui
{
    class Window : public QWidget
    {
    Q_OBJECT
    private:
        QPushButton * m_button;

    public:
        explicit Window(QWidget *parent = nullptr);

    signals:
    public slots:


    };

}
