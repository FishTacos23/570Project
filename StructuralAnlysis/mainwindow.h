#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyze.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QPolygonF>

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

    void drawDStructure();

    void on_pushButton_ZoomIn_clicked();

    void on_pushButton_ZOut_clicked();

    void on_actionClear_triggered();

    void on_pushButton_solve_released();

    void on_horizontalSlider_scaleDisp_sliderMoved(int position);

    void drawConstraints();

    void drawForces();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *myStrucLine;
    QGraphicsEllipseItem *myStructCirc;
    Analyze myStruct();
    bool solved;
    double zoom;
    double dDeform;
    QGraphicsRectItem *noRot;
    QGraphicsPolygonItem *noTrans;
    QGraphicsTextItem *myText;
    QPolygonF noTransShape;
    QFont font;
    double xmax;
    double xmin;
    double ymax;
    double ymin;

};

#endif // MAINWINDOW_H
