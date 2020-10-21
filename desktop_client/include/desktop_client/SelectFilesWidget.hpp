#pragma once

#include <QWidget>
#include <QString>

#include <u_interfaces/ui_SelectFilesWidget.h>


class SelectFilesWidget : public QWidget, public Ui::SelectFilesWidget
{
    Q_OBJECT
public:
    explicit SelectFilesWidget(QWidget* parent = nullptr);
    ~SelectFilesWidget() override = default;

public:
    QStringList getAllPaths() const;

private slots:
    void addFiles();
    void excludeFile();

};
