#pragma once

#include <QDialog>

#include <u_interfaces/ui_SortDialog.h>

class SortDialog : public QDialog, public Ui::SortDialog
{
    Q_OBJECT
public:
    explicit SortDialog(QWidget * parent = nullptr);

    void setColumnRange(QChar first, QChar last);

};
