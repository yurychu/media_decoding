
#include <desktop_client/GoToCellDialog.hpp>

#include <QRegExp>
#include <QRegExpValidator>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QRegExp regExp {"[A-Za-z][1-9][0-9]{0,2}"};
    auto regExpValidator = new QRegExpValidator{regExp, this};
    lineEdit->setValidator(regExpValidator);

    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}
