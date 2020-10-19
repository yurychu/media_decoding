
#include <desktop_client/MxfSpecificParameters.hpp>

#include <QFileDialog>

#include <mxf_specific_parameters_lib/MxfInfo.hpp>

#include <iostream>


MxfSpecificParameters::MxfSpecificParameters()
    : QWidget{nullptr}
{
    setupUi(this);

    QObject::connect(selectFileButton, SIGNAL(clicked()),
                     this, SLOT(open()));



}

void MxfSpecificParameters::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open mxf file"), ".",
                                                    tr("Mxf files (*.mxf)"));
    selectedFileLineEdit->setText(fileName);

    checkMxfFile();
}

void MxfSpecificParameters::checkMxfFile()
{
    const auto fileName = selectedFileLineEdit->text();
    std::cout << "Check mxf file: " << fileName.toStdString() << std::endl;
    mxf_info::MxfInfo mxf_info {fileName.toStdString()};

    std::cout << "Format version: " << mxf_info.getFormatVersion() << std::endl;
    std::cout << "Format profile: " << mxf_info.getFormatProfile() << std::endl;

}
