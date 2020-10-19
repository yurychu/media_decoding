#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = nullptr);

signals:
    void find_next(const QString& str, Qt::CaseSensitivity cs);
    void find_prev(const QString& str, Qt::CaseSensitivity cs);

private slots:
    void on_find_clicked();
    void enable_find_button(const QString& text);

private:
    QLabel* m_label;
    QLineEdit* m_line_edit;
    QCheckBox* m_case_check_box;
    QCheckBox* m_backward_check_box;
    QPushButton* m_find_button;
    QPushButton* m_close_button;

};
