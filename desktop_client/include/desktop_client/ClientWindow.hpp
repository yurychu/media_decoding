#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class ClientInterface; }
QT_END_NAMESPACE

namespace md_ui
{

    class ClientWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        Ui::ClientInterface *ui;

    public:
        explicit ClientWindow(QWidget *parent = nullptr);
        ~ClientWindow();

    };


}
