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

    void on_actionSave_Results_triggered();

    void readFile(std::string fileName);

    void drawStructure();

    void on_pushButton_ZoomIn_clicked();

    void on_pushButton_ZOut_clicked();

    void on_actionClear_triggered();

    void on_pushButton_solve_released();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *myStrucLine;
    Analyze myStruct();
    double zoom;

};

#endif // MAINWINDOW_H
