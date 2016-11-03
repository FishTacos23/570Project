#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    // read setup file

    // draw structure
}

void MainWindow::on_actionSolve_triggered()
{
    // perform calculations

    // clear drawing

    // draw new structure
}

void MainWindow::on_actionSave_Results_triggered()
{
    // write results to file
}
