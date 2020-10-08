#pragma once

#include <QDialog>

#include <u_interfaces/ui_SortDialog.h>

class SortDialog : public QDialog, public Ui::SortDialog
{
    Q_OBJECT
public:
    SortDialog(QWidget * parent = nullptr);

    void SetColumnRange(QChar first, QChar last);

};
