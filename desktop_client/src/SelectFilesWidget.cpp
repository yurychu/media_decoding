
#include <desktop_client/SelectFilesWidget.hpp>

#include <QFileDialog>


SelectFilesWidget::SelectFilesWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);

    QObject::connect(addFilesPushButton, SIGNAL(clicked()), this, SLOT(addFiles()));
    QObject::connect(excludeFileButton, SIGNAL(clicked()), this, SLOT(excludeFile()));

}


void SelectFilesWidget::addFiles()
{
    QString dir {"."};

    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                    tr("Open files"), dir,
                                                    tr("Mxf files (*.mxf *.MXF)"));
    for (const auto & elem : fileNames){
        fileNamesListWidget->addItem(elem);
    }

}


void SelectFilesWidget::excludeFile()
{
    const auto selectedItem = fileNamesListWidget->currentRow();
    const auto item = fileNamesListWidget->takeItem(selectedItem);
    delete item;

}


QStringList SelectFilesWidget::getAllPaths() const
{
    QStringList resultList;
    for (int i = 0; i < fileNamesListWidget->count(); ++i){
        const auto item = fileNamesListWidget->item(i);
        if (item){
            resultList.push_back(item->text());
        }
    }
    return resultList;
}
