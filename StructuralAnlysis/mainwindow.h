#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyze.h"
#include <QGraphicsScene>

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

    void drawStructure();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *myStrucLine;
    Analyze myStruct();

};

#endif // MAINWINDOW_H
