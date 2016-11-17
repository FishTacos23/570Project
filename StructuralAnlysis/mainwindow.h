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
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

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

    void on_actionClear_triggered();

    void on_pushButton_solve_released();

    void on_horizontalSlider_scaleDisp_sliderMoved(int position);

    void drawConstraints();

    void drawForces();

    void on_pushButton_Disp_released();

    void on_pushButton_Stress_released();

    void on_checkBox_const_toggled(bool checked);

    void on_checkBox_Force_toggled(bool checked);

    void wheelEvent(QWheelEvent *event);

    void zoomIn();

    void zoomOut();

    void on_actionJoints_triggered();

    void on_pushButton_addJoint_released();

    void drawJoint();

    void drawMembers();

    void on_actionMembers_triggered();

    void on_pushButton_addmember_released();

    void clearToolbars();

    void on_actionConstraints_triggered();

    void on_pushButton_addconstraint_released();

    void on_pushButton_addforce_released();

    void drawDConstraints();

    void drawDForces();

    void on_actionForces_triggered();

    void on_actionProperties_triggered();

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

    std::vector<QGraphicsEllipseItem*> drawnJoints;
    std::vector<QGraphicsLineItem*> drawnMembers;
    std::vector<std::vector<QGraphicsItem*>> drawnConstr;

    QPolygonF noDrawnTransShape;
    QGraphicsRectItem *noDrawnRot;
    QGraphicsPolygonItem *noDrawnTrans;

    double xmax;
    double xmin;
    double ymax;
    double ymin;

    bool constraint;
    bool force;
    bool displace;
    bool stress;

    bool jToolBarActive;
    bool mToolBarActive;
    bool cToolBarActive;
    bool fToolBarActive;

    QLineEdit *addXText;
    QLineEdit *addYText;

    QPushButton *addJoint;
    QPushButton *addMember;
    QPushButton *addConstraint;
    QPushButton *addForce;

    QRadioButton *constX;
    QRadioButton *constY;
    QRadioButton *constRz;

    QToolBar *jointToolBar;
    QToolBar *memberToolBar;
    QToolBar *constraintToolBar;
    QToolBar *forceToolBar;

};

#endif // MAINWINDOW_H
