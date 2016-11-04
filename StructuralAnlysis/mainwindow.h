#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyze.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSolve_triggered();

    void on_actionSave_Results_triggered();

    void readFile(std::string fileName);

private:
    Ui::MainWindow *ui;
    Analyze myStruct();

};

#endif // MAINWINDOW_H
