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
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>

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
    void selectS();
    void drawMemMap();

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
    void redoFile(int num);

    // draw joint nums
    void drawJNums();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *myStrucLine;
    QGraphicsEllipseItem *myStructCirc;
    Analyze myStruct();
    bool solved;
    double zoom;
    double dDeform;
    std::vector<QGraphicsTextItem*> myText;
    std::vector<QGraphicsTextItem*> jText;
    std::vector<QGraphicsTextItem*> rText;
    QPolygonF noTransShape;
    QFont font;

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

    int smem;

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
    bool sToolBarActive;
    bool opening;

    // Line Edits
    QLineEdit *addXText;
    QLineEdit *addYText;
    QLineEdit *addE;
    QLineEdit *addI;
    QLineEdit *addA;
    QLineEdit *adde1;
    QLineEdit *adde2;

    // Widgets
    QWidget *jointWidgX;
    QWidget *jointWidgY;
    QWidget *jointWidgZ;
    QWidget *jointWidg1;
    QWidget *jointWidg2;
    QWidget *jointWidg;
    QWidget *momWidg;
    QWidget *magWidg;
    QWidget *PropWidg;

    // Labels
    QLabel *Title;
    QLabel *JText;
    QLabel *XText;
    QLabel *YText;
    QLabel *ZText;
    QLabel *FText;
    QLabel *MText;
    QLabel *SText;
    QLabel *EText;
    QLabel *IText;
    QLabel *AText;
    QLabel *e1Text;
    QLabel *e2Text;

    // Layouts
    QHBoxLayout *xLay;
    QHBoxLayout *yLay;
    QHBoxLayout *jLay;
    QHBoxLayout *fLay;
    QHBoxLayout *sLay;
    QHBoxLayout *tLay;
    QHBoxLayout *mLay;
    QHBoxLayout *Elay;
    QHBoxLayout *Alay;
    QHBoxLayout *Ilay;
    QHBoxLayout *e1lay;
    QHBoxLayout *e2lay;
    QHBoxLayout *button;
    QVBoxLayout *allProps;

    // Push Buttons
    QPushButton *addJoint;
    QPushButton *addMember;
    QPushButton *addConstraint;
    QPushButton *addForce;
    QPushButton *setProps;

    // Radio Buttons
    QRadioButton *constX;
    QRadioButton *constY;
    QRadioButton *constRz;

    QSpinBox *sSelect;

    // Tool Bars
    QToolBar *jointToolBar;
    QToolBar *memberToolBar;
    QToolBar *constraintToolBar;
    QToolBar *forceToolBar;
    QToolBar *propToolBar;
    QToolBar *stressToolBar;

};

#endif // MAINWINDOW_H
