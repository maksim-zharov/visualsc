#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smproject.h"
#include <QString>
#include "sceditcontroller.h"

class FormEditorWindow;

class QSettings;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SMProject *_project;
    QSettings *_settings;
    static QString _keyLastFilePath;
    FormEditorWindow *_formEditorWindow;

private slots:
    void handleFileOpenClick();
    void handleFileSaveClick();
    void handleNewClick();
};

#endif // MAINWINDOW_H
