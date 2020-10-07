#include <QApplication>
#include <QDialog>

#include "ui_GoToCellDialog.h"

int main(int argc, char * argv[])
{
    QApplication app {argc, argv };

    Ui::GoToCellDialog ui_cell;
    QDialog * dialog = new QDialog {};
    ui_cell.setupUi(dialog);
    dialog->show();

    return app.exec();
}