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
        int m_counter;

    public:
        explicit Window(QWidget *parent = nullptr);

    signals:
        void counterReached();

    private slots:
        void slotButtonCliked(bool checked);


    };

}
