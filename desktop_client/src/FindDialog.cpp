#include <desktop_client/FindDialog.hpp>


md_ui::FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    m_label = new QLabel(tr("Find &what: "));

}
