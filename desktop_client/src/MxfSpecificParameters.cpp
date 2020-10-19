
#include <desktop_client/MxfSpecificParameters.hpp>

#include <QFileDialog>

#include <mxf_specific_parameters_lib/MxfInfo.hpp>

#include <iostream>
#include <sstream>


MxfSpecificParameters::MxfSpecificParameters()
    : QWidget{nullptr}
{
    setupUi(this);

    comboBox->clear();
    comboBox->addItem("1.1"); //"1.1", "1.2", "1.3"
    comboBox->addItem("1.2");
    comboBox->addItem("1.3");

    comboBox_2->clear();
    comboBox_2->addItem("OP-1a"); // OP-Atom, OP-1a, OP-1b, OP-1c, OP-2a, OP-2b, OP-2c, OP-3a, OP-3b, OP-3c
    comboBox_2->addItem("OP-1b");
    comboBox_2->addItem("OP-1c");
    comboBox_2->addItem("OP-2a");
    comboBox_2->addItem("OP-2b");
    comboBox_2->addItem("OP-2c");
    comboBox_2->addItem("OP-3a");
    comboBox_2->addItem("OP-3b");
    comboBox_2->addItem("OP-3c");
    comboBox_2->addItem("OP-Atom");

    QObject::connect(selectFileButton, SIGNAL(clicked()),
                     this, SLOT(open()));

    QObject::connect(startPushButton, SIGNAL(clicked()), this, SLOT(checkMxfFile()));



}

void MxfSpecificParameters::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open mxf file"), ".",
                                                    tr("Mxf files (*.mxf)"));
    selectedFileLineEdit->setText(fileName);

}

void MxfSpecificParameters::checkMxfFile()
{
    std::stringstream ss {};
    const auto fileName = selectedFileLineEdit->text();
    if (fileName.isEmpty()){
        ss << "File name is empty(). Error." << std::endl;
        resultsTextBrowser->insertPlainText(QString::fromStdString(ss.str()));
        return;
    }
    ss << "==========" << std::endl;
    ss << "Check mxf file: " << fileName.toStdString() << std::endl << std::endl;

    resultsTextBrowser->insertPlainText(QString::fromStdString(ss.str()));
    ss.str("");

    mxf_info::MxfInfo mxf_info {fileName.toStdString()};

    // format version
    ss << "----------" << std::endl;
    const auto actualFormatVersion = mxf_info.getFormatVersion();
    ss << "Actual Format version: " << actualFormatVersion << std::endl;
    const auto expectedFormatVersion = comboBox->currentText();
    ss << "Expected Format version: " << expectedFormatVersion.toStdString() << std::endl;
    resultsTextBrowser->insertPlainText(QString::fromStdString(ss.str()));
    ss.str("");
    if (actualFormatVersion != expectedFormatVersion.toStdString()){
        resultsTextBrowser->insertHtml("<b>Fail check! Not equal!</b><br><br>");
    }
    else {
        resultsTextBrowser->insertHtml("<b>Check success! Equal!</b><br><br>");
    }

    // format profile
    const auto actualFormatProfile = mxf_info.getFormatProfile();
    ss << "Actual Format profile: " << actualFormatProfile << std::endl;
    const auto expectedFormatProfile = comboBox_2->currentText();
    ss << "Expected Format profile: " << expectedFormatProfile.toStdString() << std::endl;
    resultsTextBrowser->insertPlainText(QString::fromStdString(ss.str()));
    ss.str("");
    if (actualFormatProfile != expectedFormatProfile.toStdString()){
        resultsTextBrowser->insertHtml("<b>Fail check! Not equal!</b><br><br>");
    }
    else {
        resultsTextBrowser->insertHtml("<b>Check success! Equal!</b><br><br>");
    }

    ss << "----------" << std::endl << std::endl;
    resultsTextBrowser->insertPlainText(QString::fromStdString(ss.str()));
}
