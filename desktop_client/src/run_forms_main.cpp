#include <QApplication>
#include <QDialog>

//#include "ui_GoToCellDialog.h"
//
//int main1(int argc, char * argv[])
//{
//    QApplication app {argc, argv };
//
//    Ui::GoToCellDialog ui_cell;
//    QDialog * dialog = new QDialog {};
//    ui_cell.setupUi(dialog);
//    dialog->show();
//
//    return app.exec();
//}

//
//#include <desktop_client/GoToCellDialog.hpp>
//
//int main(int argc, char * argv[])
//{
//    QApplication app{argc, argv};
//
//    GoToCellDialog *goToCellDialog = new GoToCellDialog{};
//    goToCellDialog->show();
//
//    return app.exec();
//}
//
//#include <desktop_client/SortDialog.hpp>
//
//int main(int argc, char * argv[])
//{
//    QApplication app{argc, argv};
//
//    SortDialog *sortDialog = new SortDialog{};
//    sortDialog->setColumnRange('C', 'F');
//    sortDialog->show();
//
//    return app.exec();
//}


#include <desktop_client/MainWindowSpreadSheet.hpp>

int main(int argc, char * argv[])
{
    QApplication app {argc, argv };
    MainWindowSpreadSheet main_window {};
    main_window.show();

    return app.exec();
}
