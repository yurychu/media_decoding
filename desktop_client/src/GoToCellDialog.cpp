
#include <desktop_client/GoToCellDialog.hpp>

#include <QRegExp>
#include <QRegExpValidator>
#include <QPushButton>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QRegExp regExp {"[A-Za-z][1-9][0-9]{0,2}"};
    auto regExpValidator = new QRegExpValidator{regExp, this};
    lineEdit->setValidator(regExpValidator);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
            lineEdit->hasAcceptableInput()
    );
}
