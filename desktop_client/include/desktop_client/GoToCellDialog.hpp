#pragma once

#include <QDialog>

#include <u_interfaces/ui_GoToCellDialog.h>


class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget* parent = nullptr);

private slots:
    void on_lineEdit_textChanged();

};
