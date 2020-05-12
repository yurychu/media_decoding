#include <desktop_client/FindDialog.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>


md_ui::FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    // line edit
    m_label = new QLabel(tr("Find &what: "));
    m_line_edit = new QLineEdit{};
    m_label->setBuddy(m_line_edit);

    // check boxes
    m_case_check_box = new QCheckBox{tr("Match &case")};
    m_backward_check_box = new QCheckBox{tr("Search &backward")};

    // buttons
    m_find_button = new QPushButton{tr("&Find")};
    m_find_button->setDefault(true);
    m_find_button->setEnabled(false);

    m_close_button = new QPushButton{tr("Clo&se")};

    // connect
    QObject::connect(
            m_line_edit, SIGNAL(textChanged(const QString&)),
            this, SLOT(enable_find_button(const QString&))
    );
    QObject::connect(
            m_find_button, SIGNAL(clicked()),
            this, SLOT(on_find_clicked())
    );
    QObject::connect(
            m_close_button, SIGNAL(clicked()),
            this, SLOT(close())  // hide widget, don't delete.
    );

    // layouts
    auto top_left_layout = new QHBoxLayout{};
    top_left_layout->addWidget(m_label);
    top_left_layout->addWidget(m_line_edit);

    auto left_layout = new QVBoxLayout{};
    left_layout->addLayout(top_left_layout);
    left_layout->addWidget(m_case_check_box);
    left_layout->addWidget(m_backward_check_box);

    auto right_layout = new QVBoxLayout{};
    right_layout->addWidget(m_find_button);
    right_layout->addWidget(m_close_button);
    right_layout->addStretch();

    auto main_layout = new QHBoxLayout{};
    main_layout->addLayout(left_layout);
    main_layout->addLayout(right_layout);

    setLayout(main_layout);

    setWindowTitle(tr("Find"));
    setFixedHeight(QDialog::sizeHint().height());
}


void md_ui::FindDialog::on_find_clicked()
{
    QString text = m_line_edit->text();
    Qt::CaseSensitivity cs =
            m_case_check_box->isChecked() ? Qt::CaseSensitive
                                            : Qt::CaseInsensitive;
    if (m_backward_check_box->isChecked()){
        emit find_prev(text, cs);
    }
    else {
        emit find_next(text, cs);
    }
}


void md_ui::FindDialog::enable_find_button(const QString &text)
{
    m_find_button->setEnabled(!text.isEmpty());
}
