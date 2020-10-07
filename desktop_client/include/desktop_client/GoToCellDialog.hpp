#pragma once

#include <QDialog>

#include <u_interfaces/ui_GoToCellDialog.h>


class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    explicit GoToCellDialog(QWidget* parent = nullptr);

private slots:
    void on_lineEdit_textChanged();  // setupUi автоматически подключает этот слот к сигналу lineEdit->textChanged()

};
