#pragma once

#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include <QToolBar>

#include <desktop_client/FindDialog.hpp>
//#include <desktop_client/SpreadSheet.hpp>  // todo
#include <QTableWidget>

class Spreadsheet : public QTableWidget{};

class MainWindowSpreadSheet : public QMainWindow
{
    Q_OBJECT  // Нужен, так как класс имеет собственные сигналы и слоты
public:
    MainWindowSpreadSheet();

protected:
    void closeEvent(QCloseEvent * closeEvent) override;  // Переопределяется, что бы задать вопрос об уверенности выйти.

private slots:
    void newFile();
    void open();
    bool save();  // return bool, в ответ на сигнал игнорится, но при вызове как функции - можно использовать.
    bool saveAs();  // return bool
    void find();  // here create findDialog
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    Spreadsheet *spreadsheet;
    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *selectAllAction;
    QAction *findAction;
    QAction *goToCellAction;
    QAction *recalculateAction;
    QAction *sortAction;
    QAction *showGridAction;
    QAction *autoRecalcAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

};
