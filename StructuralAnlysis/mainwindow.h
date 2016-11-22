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
#include <QWindow>

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
    // File Actions
    void on_actionOpen_triggered();
    void on_actionSave_Results_triggered();
    void on_actionClear_triggered();

    // Insert Actions
    void on_actionJoints_triggered();
    void on_actionMembers_triggered();
    void on_actionConstraints_triggered();
    void on_actionForces_triggered();
    void on_actionProperties_triggered();

    // Buttons and Toggles
    void on_pushButton_solve_released();
    void on_pushButton_Disp_released();
    void on_horizontalSlider_scaleDisp_sliderMoved(int position);
    void on_pushButton_Stress_released();
    void on_checkBox_const_toggled(bool checked);
    void on_checkBox_Force_toggled(bool checked);

    // draw structure
    void drawJoint();
    void drawMembers();
    void drawConstraints();
    void drawForces();
    void drawDStructure();

    // tool bar buttons
    void pushButton_addJoint();
    void pushButton_addmember();
    void pushButton_addconstraint();
    void pushButton_addforce();
    void pushButton_setDProperties();

    // view methods
    void wheelEvent(QWheelEvent *event);
    void zoomIn();
    void zoomOut();

    // other methods
    void readFile(std::string fileName);
    void clearToolbars();
    void solveReady();

    // undo things
    void on_actionUndo_triggered();
    void clearJoint();
    void clearMember();
    void clearConstraint();
    void clearForce();
    void clearFile(int num);
    void clearDraw();

    // redo things
    void on_actionRedo_triggered();
    void redoJoint();
    void redoMember();
    void redoConstraint();
    void redoForce();

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

    // drawn objects
    std::vector<QGraphicsEllipseItem*> drawnJoints;
    std::vector<QGraphicsLineItem*> drawnMembers;

    QPolygonF noDrawnTransShape;
    QGraphicsRectItem *noDrawnRot;
    QGraphicsPolygonItem *noDrawnTrans;

    // undo and redo
    std::vector<std::vector<std::string>> undoList;
    std::vector<std::vector<std::string>> redoList;
    std::vector<std::vector<double>> undidXStruct;
    std::vector<std::vector<int>> undidConn;
    std::vector<std::vector<double>> undidLoad;
    std::vector<std::vector<int>> undidConst;

    double xmax;
    double xmin;
    double ymax;
    double ymin;

    // checks
    bool constraint;
    bool force;
    bool displace;
    bool stress;
    bool jToolBarActive;
    bool mToolBarActive;
    bool cToolBarActive;
    bool fToolBarActive;
    bool pToolBarActive;

    QLineEdit *addXText;
    QLineEdit *addYText;
    QLineEdit *addE;
    QLineEdit *addI;
    QLineEdit *addA;
    QLineEdit *adde1;
    QLineEdit *adde2;

    QPushButton *addJoint;
    QPushButton *addMember;
    QPushButton *addConstraint;
    QPushButton *addForce;
    QPushButton *setProps;

    QRadioButton *constX;
    QRadioButton *constY;
    QRadioButton *constRz;

    QToolBar *jointToolBar;
    QToolBar *memberToolBar;
    QToolBar *constraintToolBar;
    QToolBar *forceToolBar;
    QToolBar *propToolBar;

};

#endif // MAINWINDOW_H
