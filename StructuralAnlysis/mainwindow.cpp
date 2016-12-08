// /////////////////////////////////////////////////////////////////////////////////////////////////////
// Title:           Spencer's Structural Analysis Program
// Description:     Solve and Visualize Displacements and Reaction Forces on Structures
// Author:          Spencer Bunnell
// Date:            October 2016
// /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "tokenize.h"
#include <fstream>
#include "analyze.h"
#include <iostream>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QToolBar>
#include <QLineEdit>
#include <QLayout>
#include <QRadioButton>
#include <QPicture>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <fstream>
#include <QSpinBox>
#include <QMatrix4x4>
#include <QScrollBar>
#include <QTextBrowser>

// global variables
static Analyze myStructure;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
//    SceneListener()
{
    ui->setupUi(this);
    QMainWindow::showMaximized();

    // initialize checks and states
    solved = false;
    displace = false;
    jToolBarActive = false;
    mToolBarActive = false;
    cToolBarActive = false;
    fToolBarActive = false;
    pToolBarActive = false;
    sToolBarActive = false;
    ui->graphicsView->verticalScrollBar()->blockSignals(true);
    ui->graphicsView->horizontalScrollBar()->blockSignals(true);

    // set up graphics scene
    scene = new CustomScene();
//    scene->addSceneListener(this);

    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::ScrollChange()
//{
//    //Do stuff to scroll bars

//}

void MainWindow::on_actionOpen_triggered()
{

    // get file name
    QString fileNameQ = QFileDialog::getOpenFileName(this,"Open Shape File", "","*.txt");
    std::string fileName = fileNameQ.toStdString();

//    std::string fileName = "C:\\Users\\Spencer\\Documents\\570project\\build-StructuralAnlysis-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\StructureInput2.6.txt";

    // check file for errors
    try
    {
        // set states
        opening = true;
        on_actionClear_triggered();

        // read in file
        readFile(fileName);

        // set magnification
        zoom = 1;

        // draw to scene
        drawThings();

        // set new states
        opening = false;
        setStates();
    }
    catch(std::invalid_argument)
    {
        // diplay open file failed message
        QMessageBox noGood;

        noGood.setText("File Formatt is Incorrect");
        noGood.setInformativeText("please follow example file");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::on_actionSave_Results_triggered()
{
    // write results to file

    // get file name
    QString fileNameQ = QFileDialog::getSaveFileName(this,"Save Results File", "","*.txt");
    std::string outPutFile = fileNameQ.toStdString();

    // create and open file
    std::ofstream solOutPut;
    solOutPut.open(outPutFile);

    // loop through displacements
    for(uint i = 0; i < myStructure.dxstruct.size(); i++)
    {
        solOutPut << "Joint " << std::to_string(i+1) << "\t"
                  << "dX = " << std::to_string(myStructure.dxstruct[i][0]) << "\t"
                  << "dY = " << std::to_string(myStructure.dxstruct[i][1]) << std::endl;
    }

    // loop through member reactions
    for(uint i = 0; i < myStructure.rmem.size(); i++)
    {
        solOutPut << "Member " << std::to_string(i+1) << "\t"
                  << "Axial 1 = " << std::to_string(myStructure.rmem[i][0]) << "\t"
                  << "Shear 1 = " << std::to_string(myStructure.rmem[i][1]) << "\t"
                  << "Moment 1 = " << std::to_string(myStructure.rmem[i][2]) << "\t"
                  << "Axial 2 = " << std::to_string(myStructure.rmem[i][3]) << "\t"
                  << "Shear 2 = " << std::to_string(myStructure.rmem[i][4]) << "\t"
                  << "Moment 2 = " << std::to_string(myStructure.rmem[i][5]) << std::endl;
    }

    // close file
    solOutPut.close();
}

void MainWindow::on_actionClear_triggered()
{
    if(opening) // no need to ask user about clearing if they are opening a file
    {
        // clear the scene and window
        scene->clear();
        clearToolbars();

        // clear variables
        myStructure.xstruct.clear();
        myStructure.dxstruct.clear();
        myStructure.conn.clear();
        myStructure.constMat.clear();
        myStructure.loadMat.clear();
        myStructure.properties.clear();
        myStructure.SDOF.clear();
        myStructure.lenRot.clear();
        myStructure.clearStructVar();
        myStructure.compMtoS.clear();
        myStructure.rmem.clear();

        // set states
        solved = false;
        displace = false;
        stress = false;
        jToolBarActive = false;
        mToolBarActive = false;
        cToolBarActive = false;
        fToolBarActive = false;
        pToolBarActive = false;
    }
    else
    {
        // ask user if they are sure
        QMessageBox sure;

        sure.setText("Are you sure you want to clear?");
        sure.setInformativeText("You may not undo this action.");
        sure.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        sure.setDefaultButton(QMessageBox::Cancel);
        sure.setWindowTitle("WARNING");
        int ret = sure.exec();

        switch (ret) {
        case QMessageBox::Ok: // if user clicks ok

            // clear the scene and window
            scene->clear();
            clearToolbars();

            // clear variables
            myStructure.xstruct.clear();
            myStructure.dxstruct.clear();
            myStructure.conn.clear();
            myStructure.constMat.clear();
            myStructure.loadMat.clear();
            myStructure.properties.clear();
            myStructure.SDOF.clear();
            myStructure.lenRot.clear();
            myStructure.clearStructVar();
            myStructure.compMtoS.clear();
            myStructure.rmem.clear();

            // set states
            solved = false;
            displace = false;
            stress = false;
            jToolBarActive = false;
            mToolBarActive = false;
            cToolBarActive = false;
            fToolBarActive = false;
            pToolBarActive = false;

            break;
        case QMessageBox::Cancel: // do nothing if cancel
            break;

        default: // do nothing if else
            break;
        }
    }

    // set states
    setStates();
}

void MainWindow::on_actionJoints_triggered()
{
    // pointers deleted when clear tool bars is called

    // clear and set states
    clearToolbars();
    jToolBarActive = true;
    setStates();

    // create toolbars and widgets
    jointToolBar = new QToolBar("Place Joints  ");
    jointWidgX = new QWidget;
    jointWidgY = new QWidget;

    // add labels
    Title = new QLabel;
    XText = new QLabel("X:");
    YText = new QLabel("Y:");

    // insert button and text
    addJoint = new QPushButton("ADD");
    addXText = new QLineEdit;
    addYText = new QLineEdit;

    // formatting
    addJoint->setDefault(true);
    Title->setTextFormat(Qt::RichText);
    Title->setText("<b><u> Insert Joints");
    addXText->setMaximumWidth(60);
    addYText->setMaximumWidth(60);
    jointToolBar->setMaximumWidth(500);
    jointToolBar->isMovable();

    // add layouts
    xLay = new QHBoxLayout();
    xLay->addWidget(XText);
    xLay->addWidget(addXText);

    yLay = new QHBoxLayout();
    yLay->addWidget(YText);
    yLay->addWidget(addYText);

    jointWidgX->setLayout(xLay);
    jointWidgY->setLayout(yLay);

    // add widgets to toolbar
    jointToolBar->addWidget(Title);
    jointToolBar->addSeparator();
    jointToolBar->addWidget(jointWidgX);
    jointToolBar->addSeparator();
    jointToolBar->addWidget(jointWidgY);
    jointToolBar->addSeparator();
    jointToolBar->addWidget(addJoint);

    // add toolbar
    this->addToolBar(jointToolBar);

    // set signal and slot
    connect(addJoint,SIGNAL(clicked()),this,SLOT(pushButton_addJoint()));
}

void MainWindow::on_actionMembers_triggered()
{
    // pointers deleted when clear tool bars is called

    // clear tool bars and set states
    clearToolbars();
    mToolBarActive = true;
    setStates();

    // create toolbar and widgets
    memberToolBar = new QToolBar("Place Members");
    jointWidg1 = new QWidget;
    jointWidg2 = new QWidget;

    // add labels
    Title = new QLabel;
    FText = new QLabel("1st:");
    SText = new QLabel("2nd:");

    // insert button and text
    addMember = new QPushButton("ADD");
    addXText = new QLineEdit;
    addYText = new QLineEdit;

    // formatting
    addMember->setDefault(true);
    memberToolBar->isMovable();
    Title->setTextFormat(Qt::RichText);
    Title->setText("<b><u> Insert Members  ");
    addXText->setMaximumWidth(30);
    addYText->setMaximumWidth(30);
    FText->setMaximumWidth(30);
    SText->setMaximumWidth(30);
    memberToolBar->setMaximumWidth(500);

    // add layouts
    xLay = new QHBoxLayout();
    xLay->addWidget(FText);
    xLay->addWidget(addXText);

    yLay = new QHBoxLayout();
    yLay->addWidget(SText);
    yLay->addWidget(addYText);

    jointWidg1->setLayout(xLay);
    jointWidg2->setLayout(yLay);

    // add widgets to toolbar
    memberToolBar->addWidget(Title);
    memberToolBar->addSeparator();
    memberToolBar->addWidget(jointWidg1);
    memberToolBar->addWidget(jointWidg2);
    memberToolBar->addWidget(addMember);

    // add toolbar
    this->addToolBar(memberToolBar);

    // connect signals and slots
    connect(addMember,SIGNAL(clicked()),this,SLOT(pushButton_addmember()));
}

void MainWindow::on_actionConstraints_triggered()
{
    // pointers deleted when clear tool bars is called

    // clear toolbars and set states
    clearToolbars();
    cToolBarActive = true;
    setStates();

    // create toolbar and widgets
    constraintToolBar = new QToolBar("Place Constraint");
    jointWidg = new QWidget;
    jointWidgX = new QWidget;
    jointWidgY = new QWidget;
    jointWidgZ = new QWidget;

    // add labels
    Title = new QLabel;
    JText = new QLabel("Joint:");
    XText = new QLabel("X:");
    YText = new QLabel("Y:");
    ZText = new QLabel("Rz:");

    // insert button and Line
    addConstraint = new QPushButton("ADD");
    addXText = new QLineEdit;
    constX = new QRadioButton;
    constY = new QRadioButton;
    constRz = new QRadioButton;

    // formatting
    constraintToolBar->isMovable();
    Title->setTextFormat(Qt::RichText);
    Title->setText("<b><u> Set Constraints  ");
    addXText->setMaximumWidth(30);
    JText->setMaximumWidth(45);
    addConstraint->setDefault(true);
    constraintToolBar->setMaximumWidth(600);

    // add layouts
    jLay = new QHBoxLayout();
    jLay->addWidget(JText);
    jLay->addWidget(addXText);

    fLay = new QHBoxLayout();
    fLay->addWidget(XText);
    fLay->addWidget(constX);

    sLay = new QHBoxLayout();
    sLay->addWidget(YText);
    sLay->addWidget(constY);

    tLay = new QHBoxLayout();
    tLay->addWidget(ZText);
    tLay->addWidget(constRz);

    jointWidg->setLayout(jLay);
    jointWidgX->setLayout(fLay);
    jointWidgY->setLayout(sLay);
    jointWidgZ->setLayout(tLay);

    // add widgets to tool bar
    constraintToolBar->addWidget(Title);
    constraintToolBar->addSeparator();
    constraintToolBar->addWidget(jointWidg);
    constraintToolBar->addWidget(jointWidgX);
    constraintToolBar->addWidget(jointWidgY);
    constraintToolBar->addWidget(jointWidgZ);
    constraintToolBar->addWidget(addConstraint);

    // toggle constraints
    ui->checkBox_const->setChecked(true);

    // add toolbar
    this->addToolBar(constraintToolBar);

    // connect signals and slot
    connect(addConstraint,SIGNAL(clicked()),this,SLOT(pushButton_addconstraint()));
}

void MainWindow::on_actionForces_triggered()
{
    // pointers deleted when clear tool bars is called

    // clear toolbars and set states
    clearToolbars();
    fToolBarActive = true;
    setStates();

    // create toolbar and widgets
    forceToolBar = new QToolBar("Place Force");
    jointWidg = new QWidget;
    jointWidgX = new QWidget;
    jointWidgY = new QWidget;
    momWidg = new QWidget;
    magWidg = new QWidget;

    // add labels
    Title = new QLabel;
    JText = new QLabel("Joint:");
    MText = new QLabel("Magnitude:");
    XText = new QLabel("X:");
    YText = new QLabel("Y:");
    ZText = new QLabel("Rz:");

    // insert button and lines
    addForce = new QPushButton("ADD");
    addXText = new QLineEdit;
    addYText = new QLineEdit;
    constX = new QRadioButton;
    constY = new QRadioButton;
    constRz = new QRadioButton;

    // formatting
    Title->setTextFormat(Qt::RichText);
    Title->setText("<b><u> Place Forces  ");
    forceToolBar->isMovable();
    addXText->setMaximumWidth(30);
    addYText->setMaximumWidth(60);
    JText->setMaximumWidth(40);
    MText->setMaximumWidth(80);
    addForce->setDefault(true);
    forceToolBar->setMaximumWidth(800);

     // add layouts
    jLay = new QHBoxLayout();
    jLay->addWidget(JText);
    jLay->addWidget(addXText);

    mLay = new QHBoxLayout();
    mLay->addWidget(MText);
    mLay->addWidget(addYText);

    fLay = new QHBoxLayout();
    fLay->addWidget(XText);
    fLay->addWidget(constX);

    sLay = new QHBoxLayout();
    sLay->addWidget(YText);
    sLay->addWidget(constY);

    tLay = new QHBoxLayout();
    tLay->addWidget(ZText);
    tLay->addWidget(constRz);

    jointWidg->setLayout(jLay);
    jointWidgX->setLayout(fLay);
    jointWidgY->setLayout(sLay);
    momWidg->setLayout(tLay);
    magWidg->setLayout(mLay);

    // add widgets to tool bar
    forceToolBar->addWidget(Title);
    forceToolBar->addSeparator();
    forceToolBar->addWidget(jointWidg);
    forceToolBar->addWidget(magWidg);
    forceToolBar->addWidget(jointWidgX);
    forceToolBar->addWidget(jointWidgY);
    forceToolBar->addWidget(momWidg);
    forceToolBar->addWidget(addForce);

    // toggle forces
    ui->checkBox_Force->setChecked(true);

    // add tool bar
    this->addToolBar(forceToolBar);

    // connect signals and slot
    connect(addForce,SIGNAL(clicked()),this,SLOT(pushButton_addforce()));
}

void MainWindow::on_actionProperties_triggered()
{
    // pointers deleted when clear tool bars is called

    // clear toolbars and set states
    clearToolbars();
    pToolBarActive = true;
    setStates();

    // create toolbar and widgets
    propToolBar = new QToolBar("Set Properties");
    PropWidg = new QWidget;

    // create buttons and labels
    setProps = new QPushButton("SET");
    Title = new QLabel;
    EText = new QLabel("E: ");
    IText = new QLabel("I:  ");
    AText = new QLabel("A: ");
    e1Text = new QLabel("e1:");
    e2Text = new QLabel("e2:");

    // add line edits
    addE = new QLineEdit;
    addA = new QLineEdit;
    addI = new QLineEdit;
    adde1 = new QLineEdit;
    adde2 = new QLineEdit;

    // formatting
    Title->setTextFormat(Qt::RichText);
    Title->setText("<b><u> Structural Properties");
    addE->setMaximumWidth(100);
    addA->setMaximumWidth(100);
    addI->setMaximumWidth(100);
    adde1->setMaximumWidth(100);
    adde2->setMaximumWidth(100);
    setProps->setDefault(true);

    // add layouts
    Elay = new QHBoxLayout;
    Elay->addSpacing(25);
    Elay->addWidget(EText);
    Elay->addWidget(addE);
    Elay->addSpacing(25);

    Alay = new QHBoxLayout;
    Alay->addSpacing(25);
    Alay->addWidget(AText);
    Alay->addWidget(addA);
    Alay->addSpacing(25);

    Ilay = new QHBoxLayout;
    Ilay->addSpacing(25);
    Ilay->addWidget(IText);
    Ilay->addWidget(addI);
    Ilay->addSpacing(25);

    e1lay = new QHBoxLayout;
    e1lay->addSpacing(25);
    e1lay->addWidget(e1Text);
    e1lay->addWidget(adde1);
    e1lay->addSpacing(25);

    e2lay  = new QHBoxLayout;
    e2lay->addSpacing(25);
    e2lay->addWidget(e2Text);
    e2lay->addWidget(adde2);
    e2lay->addSpacing(25);

    button = new QHBoxLayout;
    button->addSpacing(15);
    button->addWidget(setProps);
    button->addSpacing(15);

    allProps = new QVBoxLayout;
    allProps->addWidget(Title);
    allProps->addSpacing(3);
    allProps->addLayout(Elay);
    allProps->addLayout(Alay);
    allProps->addLayout(Ilay);
    allProps->addLayout(e1lay);
    allProps->addLayout(e2lay);
    allProps->addLayout(button);
    PropWidg->setLayout(allProps);

    // add widgets to toolbar
    propToolBar->addWidget(PropWidg);

    // add toolbar
    this->addToolBar(Qt::LeftToolBarArea,propToolBar);

    // add signals and slots
    connect(setProps,SIGNAL(clicked()),this,SLOT(pushButton_setDProperties()));
}

void MainWindow::on_pushButton_solve_released()
{
    if(!solved)
    {
        // no clicking undo or redo after this point
        undoList.clear();
        redoList.clear();

        // set mouse to hourglass
        QApplication::setOverrideCursor(Qt::BusyCursor);

        // perform sturctural calculation and set progress bar
        myStructure.preprocessing();
            ui->progressBar->setValue(5);

        myStructure.AssembleStructStiff();
            ui->progressBar->setValue(15);

        myStructure.Triangularization();
            ui->progressBar->setValue(65);

        myStructure.AssembleStructForce();
            ui->progressBar->setValue(75);

        myStructure.BackSub();
            ui->progressBar->setValue(95);

        myStructure.postprocessing();
            ui->progressBar->setValue(100);

        // set states
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        dDeform = 1;
        solved = true;
        setStates();
    }
}

void MainWindow::on_pushButton_Disp_released()
{
    // clear window of tool bars
    clearToolbars();

    // set state
    displace = true;
    setStates();

    // draw to scene
    drawThings();
}

void MainWindow::on_horizontalSlider_scaleDisp_sliderMoved(int position)
{
    if(displace)
    {
        // set magnification
        dDeform = position;

        // draw to screen
        drawThings();
    }
}

void MainWindow::on_pushButton_Stress_released()
{
    // pointers deleted on clear tool bar

    // set states
    sToolBarActive = true;
    displace = false;
    stress = true;
    setStates();

    // add tool bar to toggle members
    // new toolbar items
    stressToolBar = new QToolBar("Select Joint  ");
    JText = new QLabel;
    sSelect = new QSpinBox;
    jLay = new QHBoxLayout;
    jointWidg = new QWidget;

    // format
    JText->setTextFormat(Qt::RichText);
    JText->setText("<b><u> Member ");
    sSelect->setMaximum(myStructure.conn.size());
    sSelect->setMinimum(1);
    jLay->addWidget(JText);
    jLay->addWidget(sSelect);
    jointWidg->setLayout(jLay);

    // add to toolbar
    stressToolBar->addWidget(jointWidg);

    // add to scene
    this->addToolBar(stressToolBar);

    // connect button
    connect(sSelect,SIGNAL(valueChanged(int)),this,SLOT(selectS()));

    // draw first member
    selectS();
}

void MainWindow::on_checkBox_const_toggled(bool checked)
{
    // redraw
    drawThings();
}

void MainWindow::on_checkBox_Force_toggled(bool checked)
{
    // redraw
    drawThings();
}

void MainWindow::selectS()
{
    // draws reaction forces on members

    // Text pointers are deleted when scene is cleared

    // clear scene and Text
    scene->clear();
    rText.clear();

    // format pens/brushes
    QPen sPen(Qt::white);
    sPen.setWidth(4);
    QBrush momBrush(Qt::transparent);
    QBrush momBrush2(Qt::yellow);
    QBrush loadBrush(Qt::green);
    QPen loadPen(Qt::green);
    QPen momPen(Qt::yellow);
    loadPen.setWidth(2);
    momPen.setWidth(2);

    // set states
    bool negativeAx1 = false;
    bool negativeSh1 = false;
    bool negativeMo1 = false;
    bool negativeAx2 = false;
    bool negativeSh2 = false;
    bool negativeMo2 = false;

    // which member to show
    int s = sSelect->value()-1;

    // get information about member
    double length = myStructure.lenRot[s][0]*zoom;

    std::string ax1 = std::to_string(myStructure.rmem[s][0]);
    std::string ax2 = std::to_string(myStructure.rmem[s][3]);
    std::string sh1 = std::to_string(myStructure.rmem[s][1]);
    std::string sh2 = std::to_string(myStructure.rmem[s][4]);
    std::string mo1 = std::to_string(myStructure.rmem[s][2]);
    std::string mo2 = std::to_string(myStructure.rmem[s][5]);

    // get trimmed strings
    QString axs1 = trimString(ax1);
    QString shs1 = trimString(sh1);
    QString mos1 = trimString(mo1);
    QString axs2 = trimString(ax2);
    QString shs2 = trimString(sh2);
    QString mos2 = trimString(mo2);

    // get sign of each
    if(axs1.at(0)=='-')
    {
        axs1.remove(0,1);
        negativeAx1 = true;
    }
    if(shs1.at(0)=='-')
    {
        shs1.remove(0,1);
        negativeSh1 = true;
    }
    if(mos1.at(0)=='-')
    {
        mos1.remove(0,1);
        negativeMo1 = true;
    }
    if(axs2.at(0)=='-')
    {
        axs2.remove(0,1);
        negativeAx2 = true;
    }
    if(shs2.at(0)=='-')
    {
        shs2.remove(0,1);
        negativeSh2 = true;
    }
    if(mos2.at(0)=='-')
    {
        mos2.remove(0,1);
        negativeMo2 = true;
    }

    // axial forces /////////////////////////////////////////////////////////////////

    // add line
    scene->addLine(0,0,length,0,sPen);

    // draw forces lines
    myStrucLine = scene->addLine(0,0,-50,0,loadPen);
    myStrucLine = scene->addLine(length,0,length+50,0,loadPen);

    // create text items and push to list
    QGraphicsTextItem *newTextax1 = new QGraphicsTextItem;
    newTextax1->setDefaultTextColor(Qt::magenta);
    newTextax1->setPlainText(axs1);
    newTextax1->setX(-80);
    newTextax1->setY(5);

    rText.push_back(newTextax1);

    QGraphicsTextItem *newTextax2 = new QGraphicsTextItem;
    newTextax2->setDefaultTextColor(Qt::magenta);
    newTextax2->setPlainText(axs2);
    newTextax2->setX(length+40);
    newTextax2->setY(5);

    rText.push_back(newTextax2);

    // draw arrow heads
    // left side
    if(negativeAx1)
    {
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(-50,0) << QPointF(-30,5) << QPointF(-30,-5);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);       
    }
    else
    {
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(0,0) << QPointF(-20,5) << QPointF(-20,-5);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }
    // right side
    if(negativeAx2)
    {
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length,0) << QPointF(length+20,5) << QPointF(length+20,-5);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }
    else
    {
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length+50,0) << QPointF(length+30,5) << QPointF(length+30,-5);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }

    // shear /////////////////////////////////////////////////////////////////////////////////////////

    // create text items
    QGraphicsTextItem *newTextsh1 = new QGraphicsTextItem;
    newTextsh1->setDefaultTextColor(Qt::magenta);
    newTextsh1->setPlainText(shs1);
    QGraphicsTextItem *newTextsh2 = new QGraphicsTextItem;
    newTextsh2->setDefaultTextColor(Qt::magenta);
    newTextsh2->setPlainText(shs2);

    // left side
    if(negativeSh1)
    {
        // set text location
        newTextsh1->setX(-10);
        newTextsh1->setY(50);

        // draw line
        myStrucLine = scene->addLine(0,0,0,50,loadPen);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(0,50) << QPointF(5,30) << QPointF(-5,30);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }
    else
    {
        // set text location
        newTextsh1->setX(-10);
        newTextsh1->setY(-70);

        // draw line
        myStrucLine = scene->addLine(0,0,0,-50,loadPen);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(0,-50) << QPointF(5,-30) << QPointF(-5,-30);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }

    // add to list
    rText.push_back(newTextsh1);

    // right side
    if(negativeSh2)
    {
        // set text location
        newTextsh2->setX(length);
        newTextsh2->setY(50);

        // draw line
        myStrucLine = scene->addLine(length,0,length,50,loadPen);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length,50) << QPointF(5+length,30) << QPointF(length-5,30);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }
    else
    {
        // set text location
        newTextsh2->setX(length+10);
        newTextsh2->setY(-50);

        // draw line
        myStrucLine = scene->addLine(length,0,length,-50,loadPen);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length,-50) << QPointF(5+length,-30) << QPointF(length-5,-30);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);
    }

    // push to list
    rText.push_back(newTextsh2);

    // moments ///////////////////////////////////////////////////////////////////////////////////////////////

    // create texts
    QGraphicsTextItem *newTextmo1 = new QGraphicsTextItem;
    newTextmo1->setDefaultTextColor(Qt::magenta);
    newTextmo1->setPlainText(mos1);
    QGraphicsTextItem *newTextmo2 = new QGraphicsTextItem;
    newTextmo2->setDefaultTextColor(Qt::magenta);
    newTextmo2->setPlainText(mos2);

    // draw circles
    myStructCirc = scene->addEllipse(-20, -20, 40, 40, momPen, momBrush);
    myStructCirc = scene->addEllipse(length-20, -20, 40, 40, momPen, momBrush);

    // left side
    if(negativeMo1)
    {
        // set text location
        newTextmo1->setX(20);
        newTextmo1->setY(-30);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(10,-20) << QPointF(-10,-15) << QPointF(-10,-25);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);
    }
    else
    {
        // set text location
        newTextmo1->setX(20);
        newTextmo1->setY(-30);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(-10,-20) << QPointF(10,-15) << QPointF(10,-25);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);
    }

    // push text to list
    rText.push_back(newTextmo1);

    // right side
    if(negativeMo2)
    {
        // set text location
        newTextmo2->setX(length+20);
        newTextmo2->setY(-30);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length+10,-20) << QPointF(length-10,-15) << QPointF(length-10,-25);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);
    }
    else
    {
        // set text location
        newTextmo2->setX(length+20);
        newTextmo2->setY(-30);

        // draw arrow head
        noDrawnTransShape.clear();
        noDrawnTransShape << QPointF(length-10,-20) << QPointF(length+10,-15) << QPointF(length+10,-25);
        noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);
    }

    // push text to list
    rText.push_back(newTextmo2);

    // draw texts scene
    for(int i = 0; i < rText.size(); i++)
        scene->addItem(rText[i]);

    // draw map
    drawMemMap();
}

void MainWindow::drawMemMap()
{
    // draw greyed- out structure to the side highlighting which member you are looking at

    // create and format and variables
    QPen noSelectPen(Qt::gray);
    QPen SelectPen(Qt::red);
    noSelectPen.setWidth(2);
    SelectPen.setWidth(3);

    double xMax = 0;
    double yMin = 0;
    double x;
    double y;

    // number from input box
    int s = sSelect->value();

    // find max x and min y of structure
    for(int i = 0; i < myStructure.xstruct.size(); i++)
    {
        x = myStructure.xstruct[i][0];
        y = myStructure.xstruct[i][1];

        if(i==0)
        {
            xMax = x;
            yMin = y;
        }
        else
        {
            if(x>xMax)
                xMax=x;
            if(y<yMin)
                yMin = y;
        }
    }

    // temporary variables
    int J1;
    int J2;
    double x1;
    double x2;
    double y1;
    double y2;
    double scale = 3;

    // draw members
    for(int i = 0; i < myStructure.conn.size(); i++)
    {
        J1 = myStructure.conn[i][0]-1;
        J2 = myStructure.conn[i][1]-1;

        x1 = myStructure.xstruct[J1][0];
        y1 = -myStructure.xstruct[J1][1];
        x2 = myStructure.xstruct[J2][0];
        y2 = -myStructure.xstruct[J2][1];

        // scale values
            // first translate center to origin
        x1 = (x1/scale - xMax)*zoom;
        x2 = (x2/scale - xMax)*zoom;
        y1 = (y1/scale - yMin)*zoom;
        y2 = (y2/scale - yMin)*zoom;

        // draw member
        if(s==i+1) // if selected draw red
            scene->addLine(x1,y1,x2,y2,SelectPen);
        else
            scene->addLine(x1,y1,x2,y2,noSelectPen);
    }
}

void MainWindow::drawThings()
{
    // clear scene
    scene->clear();

    // draw constraints
    if(ui->checkBox_const->isChecked())
        drawConstraints();

    // draw members
    drawMembers();

    // draw Joints
    drawJoint();

    // draw Forces
    if(ui->checkBox_Force->isChecked())
        drawForces();

    // label joints
    if(jToolBarActive || mToolBarActive || cToolBarActive || fToolBarActive)
        drawJNums();

    // draw displaced
    if(displace)
        drawDStructure();
}

void MainWindow::drawJoint()
{
    // set brush and pens
    QBrush jgrey(Qt::gray);
    QPen jPen(Qt::white);

    // loop through joints
    for(uint i = 0; i < myStructure.xstruct.size(); i++)
    {
        // draw ellipse
        scene->addEllipse(myStructure.xstruct[i][0]*zoom-5,-myStructure.xstruct[i][1]*zoom-5,10,10,jPen,jgrey);
    }
}

void MainWindow::drawMembers()
{
    // set pen
    QPen mPen;

    // if displaced change pen
    if(displace)
    {
        mPen.setColor(Qt::gray);
        mPen.setWidth(3);
        mPen.setStyle(Qt::DashLine);
    }
    else
    {
        mPen.setColor(Qt::white);
        mPen.setWidth(5);
    }

    // loop through members
    for(uint i = 0; i < myStructure.conn.size(); i++)
    {
        // get points from member
        int One = myStructure.conn[i][0];
        int Two = myStructure.conn[i][1];

        // get points values
        double x1 = myStructure.xstruct[One-1][0]*zoom;
        double y1 = -myStructure.xstruct[One-1][1]*zoom;
        double x2 = myStructure.xstruct[Two-1][0]*zoom;
        double y2 = -myStructure.xstruct[Two-1][1]*zoom;

        // add line to scene
        scene->addLine(x1,y1,x2,y2,mPen);
    }
}

void MainWindow::drawConstraints()
{
    // set Pens and Brushes
    QBrush constBrush(Qt::blue);
    QPen constPen(Qt::blue);
    constPen.setWidth(2);

    // loop through constraint matrix
    for(uint i = 0; i < myStructure.constMat.size(); i++)
    {
        // get constraint info
        int m = myStructure.constMat[i][0]-1;
        int dir = myStructure.constMat[i][1];

        double x1 = myStructure.xstruct[m][0]*zoom;
        double y1 = -myStructure.xstruct[m][1]*zoom;

        // draw based on direction
        if(dir==1)
        {
            // draw triangle
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-30,y1-15) << QPointF(x1-30,y1+15);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,constPen,constBrush);
        }
        else if(dir==2)
        {
            // draw triangle
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-15,y1+30) << QPointF(x1+15,y1+30);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,constPen,constBrush);
        }
        else
        {
            // draw rectangle
            noDrawnRot = scene->addRect(x1-10,y1-10,20,20,constPen,constBrush);
        }

    }
}

void MainWindow::drawForces()
{
    // text pointers deleted when scene cleared

    // empty text list
    myText.clear();

    // brush/pen creation and formatting
    QBrush momBrush(Qt::transparent);
    QBrush momBrush2(Qt::yellow);
    QBrush loadBrush(Qt::green);
    QPen loadPen(Qt::green);
    QPen momPen(Qt::yellow);
    loadPen.setWidth(2);
    momPen.setWidth(2);

    // state
    bool negative = false;

    // loop through load matrix
    for(uint i = 0; i < myStructure.loadMat.size(); i++)
    {
        // get load information
        int m = (int)myStructure.loadMat[i][0]-1;
        int dir = (int)myStructure.loadMat[i][1];
        std::string forceMag = std::to_string(myStructure.loadMat[i][2]);

        // get rid of trailing zeros
        std::string point = ".";
        int posdot = forceMag.find(point);
        int strSize = forceMag.size();

        // set state
        bool nonZero = false;

        // if dot is in string
        if(posdot < strSize)
        {
            // loop until dot
            for(int j = strSize; j >= posdot-1; j--)
            {
                // if there's a zero or dot
                if(forceMag.substr(j-1,1)=="0" || forceMag.substr(j,1)==".")
                {
                    if(!nonZero) // if value is a zero
                    {
                        forceMag.erase(j);
                    }
                }
                else
                {
                    nonZero = true;
                }
            }
        }

        // convert to QString
        QString forceT = QString::fromStdString(forceMag);

        // check negative
        if(forceT.at(0)=='-')
        {
            forceT.remove(0,1);
            negative = true;
        }

        // create new text item and set parameters
        QGraphicsTextItem *newText = new QGraphicsTextItem;

        newText->setDefaultTextColor(Qt::gray);
        newText->setPlainText(forceT);

        double x1 = myStructure.xstruct[m][0]*zoom;
        double y1 = -myStructure.xstruct[m][1]*zoom;

        // draw based on direction
        if(dir==1)
        {
            // clear triangle shape
            noDrawnTransShape.clear();

            // draw triangle and line
            if(negative)
            {
                myStrucLine = scene->addLine(x1,y1,x1-50,y1,loadPen);
                noDrawnTransShape << QPointF(x1-50,y1) << QPointF(x1-30,y1+5) << QPointF(x1-30,y1-5);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                // set text location
                newText->setX(x1-80);
                newText->setY(y1);

                // reset negative
                negative = false;
            }
            else
            {
                myStrucLine = scene->addLine(x1,y1,x1+50,y1,loadPen);
                noDrawnTransShape << QPointF(x1+50,y1) << QPointF(x1+30,y1+5) << QPointF(x1+30,y1-5);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                // set text location
                newText->setX(x1+60);
                newText->setY(y1);
            }
        }
        else if(dir==2)
        {
            // clear triangle shape
            noDrawnTransShape.clear();

            if(negative)
            {
                myStrucLine = scene->addLine(x1,y1,x1,y1+50,loadPen);
                noDrawnTransShape << QPointF(x1,y1+50) << QPointF(x1-5,y1+30) << QPointF(x1+5,y1+30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                // set text location
                newText->setX(x1+5);
                newText->setY(y1+50);

                // reset negative
                negative = false;
            }
            else
            {
                myStrucLine = scene->addLine(x1,y1,x1,y1-50,loadPen);
                noDrawnTransShape << QPointF(x1,y1-50) << QPointF(x1-5,y1-30) << QPointF(x1+5,y1-30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                // set text location
                newText->setX(x1+5);
                newText->setY(y1-50);
            }
        }
        else
        {
            // draw cirlces
            myStructCirc = scene->addEllipse(x1-20, y1-20, 40, 40, momPen, momBrush);
            noDrawnTransShape.clear();

            if(negative == true)
            {
                // draw triangle
                noDrawnTransShape << QPointF(x1+10,y1-20) << QPointF(x1-10,y1-10) << QPointF(x1-10,y1-30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);

                // set text location
                newText->setX(x1-25);
                newText->setY(y1-60);

                // reset negative
                negative = false;
            }
            else
            {
                // draw triangle
                noDrawnTransShape << QPointF(x1-10,y1-20) << QPointF(x1+10,y1-10) << QPointF(x1+10,y1-30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);

                // set text location
                newText->setX(x1-25);
                newText->setY(y1-60);
            }
        }

        // push new text to list
        myText.push_back(newText);
    }

    // loop through my Text and add to scene
    for(int i = 0; i < myText.size(); i++)
        scene->addItem(myText[i]);
}

void MainWindow::drawDStructure()
{
    // create variables
    double x1;
    double y1;
    double x2;
    double y2;

    // create and set pen
    QPen linePen(Qt::red);
    linePen.setWidth(5);

    // loop through all members
    for(uint i = 0; i < myStructure.conn.size();i++)
    {

        // get joints from members
        int m = myStructure.conn[i][0]-1;
        int n = myStructure.conn[i][1]-1;

        // get x and y with magnified displacements
        x1 = (myStructure.xstruct[m][0]+myStructure.dxstruct[m][0]*dDeform)*zoom;
        y1 = -(myStructure.xstruct[m][1]+myStructure.dxstruct[m][1]*dDeform)*zoom;
        x2 = (myStructure.xstruct[n][0]+myStructure.dxstruct[n][0]*dDeform)*zoom;
        y2 = -(myStructure.xstruct[n][1]+myStructure.dxstruct[n][1]*dDeform)*zoom;

        // add line
        myStrucLine = scene->addLine(x1,y1,x2,y2,linePen);
    }
}

void MainWindow::pushButton_addJoint()
{
    try
    {
        // state
        bool repeat = false;

        // create vector
        std::vector<double> jPoints;

        // get values for toolbar
        QString myX = addXText->text();
        QString myY = addYText->text();

        // convert to doubles
        double x = myX.toDouble();
        double y = myY.toDouble();

        // make sure points aren't already there
        for(int i = 0; i < myStructure.xstruct.size(); i++)
        {
            if(x==myStructure.xstruct[i][0] && y==myStructure.xstruct[i][1])
                repeat = true;
        }

        if(!repeat)
        {
            // add points to joint
            jPoints.push_back(x);
            jPoints.push_back(y);

            // add joint to structure
            myStructure.xstruct.push_back(jPoints);

            // add to undolist, clear redo
            std::vector<std::string> oneLine;
            oneLine.push_back("joint");
            oneLine.push_back("1");
            undoList.push_back(oneLine);
            redoList.clear();
\
            // set states
            displace = false;
            solved = false;
            stress = false;
            setStates();

            // draw to scene
            drawThings();
        }
    }
    catch(std::invalid_argument)
    {
        // message if values given don't work

        QMessageBox noGood;

        noGood.setText("Inputs Incorrect");
        noGood.setInformativeText("please follow example");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::pushButton_addmember()
{
    try
    {
        // set state
        bool repeat = false;

        // create vector of points
        std::vector<int> mPoints;

        // get values from toolbar
        QString myOne = addXText->text();
        QString myTwo = addYText->text();

        // convert to int
        int One = myOne.toInt();
        int Two = myTwo.toInt();

        // make sure they are points that exits
        if(One <= myStructure.xstruct.size() && Two <= myStructure.xstruct.size())
        {
           // make sure members aren't already there
           for(int i = 0; i < myStructure.conn.size(); i++)
           {
               if(One==myStructure.conn[i][0] && Two==myStructure.conn[i][1])
                   repeat = true;
           }

           // make sure member ends are connected to same joint
           if(One==Two)
               repeat = true;

           if(!repeat)
           {
               // push points to vector
               mPoints.push_back(One);
               mPoints.push_back(Two);

               // push member to structure
               myStructure.conn.push_back(mPoints);

               // add to undo list, clear redo
               std::vector<std::string> oneLine;
               oneLine.push_back("member");
               oneLine.push_back("1");
               undoList.push_back(oneLine);
               redoList.clear();

               // states
               solved = false;
               displace = false;
               stress = false;
               setStates();

               // draw to scene
               drawThings();
           }
       }
       else
       {
            // message if values don't work
            QMessageBox noGood;

            noGood.setText("Inputs Incorrect");
            noGood.setInformativeText("please select existing joint");
            noGood.setStandardButtons(QMessageBox::Ok);
            noGood.setDefaultButton(QMessageBox::Ok);
            noGood.setWindowTitle("WARNING");
            noGood.exec();
       }
    }
    catch(std::invalid_argument)
    {
        // message if values don't work

        QMessageBox noGood;

        noGood.setText("Inputs Incorrect");
        noGood.setInformativeText("please follow example");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::pushButton_addconstraint()
{

    try
    {
        // state
        bool repeat = false;
        ui->checkBox_const->setChecked(true);

        // variables
        int numRep = 0;         // count number repeated
        int numOneClick = 0;    // count number in One Click
        std::vector<int> constPoint;
\
        // get values from toolbar
        QString constJoint = addXText->text();

        // convert to int
        int constJointNum = constJoint.toInt();

        // check one direction at a time
        if(constX->isChecked())
        {
            // make sure constraint aren't already there
            for(int i = 0; i < myStructure.constMat.size(); i++)
            {
                if(constJointNum==myStructure.constMat[i][0] && myStructure.constMat[i][1]==1)
                    repeat = true;
            }

            if(!repeat)
            {
                // add to structure
                constPoint.push_back(constJointNum);
                constPoint.push_back(1);
                myStructure.constMat.push_back(constPoint);
                constPoint.clear();

                numOneClick++;
            }
            else
                numRep++;

            // state
            repeat = false;
        }
        if(constY->isChecked())
        {
            // make sure points aren't already there
            for(int i = 0; i < myStructure.constMat.size(); i++)
            {
                if(constJointNum==myStructure.constMat[i][0] && myStructure.constMat[i][2]==2)
                    repeat = true;
            }

            if(!repeat)
            {
                constPoint.push_back(constJointNum);
                constPoint.push_back(2);
                myStructure.constMat.push_back(constPoint);
                constPoint.clear();

                numOneClick++;
            }
            else
                numRep++;

            // state
            repeat = false;
        }
        if(constRz->isChecked())
        {
            // make sure points aren't already there
            for(int i = 0; i < myStructure.constMat.size(); i++)
            {
                if(constJointNum==myStructure.constMat[i][0] && myStructure.constMat[i][2]==3)
                    repeat = true;
            }

            if(!repeat)
            {
                constPoint.push_back(constJointNum);
                constPoint.push_back(3);
                myStructure.constMat.push_back(constPoint);
                constPoint.clear();

                numOneClick++;
            }
            else
                numRep;
        }

        // as long as there was one new constraint
        if(numRep!=3)
        {
            // add to undo List
            std::string NumConst;
            NumConst = std::to_string(numOneClick);
            std::vector<std::string> oneLine;
            oneLine.push_back("constraint");
            oneLine.push_back(NumConst);
            undoList.push_back(oneLine);
            redoList.clear();

            // states
            solved = false;
            displace = false;
            setStates();

            // draw on scene
            drawThings();           
        }
    }
    catch(std::invalid_argument)
    {
        // message if inputs bad

        QMessageBox noGood;

        noGood.setText("Inputs Incorrect");
        noGood.setInformativeText("please follow example");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::pushButton_addforce()
{

    try
    {
        // state
        bool repeat = false;
        ui->checkBox_Force->setChecked(true);

        // variables
        int numRep = 0;         // number of repeated
        int numOneClick = 0;    // number in one click
        std::vector<double> forcePoint;

        // get values from toolbar
        QString forceJoint = addXText->text();
        QString forceMag = addYText->text();

        // convert to doulbe
        double forceJointNum = forceJoint.toInt();
        double forceDoubleMag = forceMag.toDouble();

        // check each direction
        if(constX->isChecked())
        {
            // make sure force isn't already there
            for(int i = 0; i < myStructure.loadMat.size(); i++)
            {
                if(forceJointNum==myStructure.loadMat[i][0] && myStructure.loadMat[i][1]==1)
                    repeat = true;
            }

            if(!repeat)
            {
                // add to structure
                forcePoint.push_back(forceJointNum);
                forcePoint.push_back(1);
                forcePoint.push_back(forceDoubleMag);
                myStructure.loadMat.push_back(forcePoint);
                forcePoint.clear();

                numOneClick++;
            }
            else
                numRep++;

            //state
            repeat = false;
        }
        if(constY->isChecked())
        {
            // make sure points aren't already there
            for(int i = 0; i < myStructure.loadMat.size(); i++)
            {
                if(forceJointNum==myStructure.loadMat[i][0] && myStructure.loadMat[i][1]==2)
                    repeat = true;
            }

            if(!repeat)
            {
                // add to structure
                forcePoint.push_back(forceJointNum);
                forcePoint.push_back(2);
                forcePoint.push_back(forceDoubleMag);
                myStructure.loadMat.push_back(forcePoint);
                forcePoint.clear();

                numOneClick++;
            }
            else
                numRep++;

            // state
            repeat = false;
        }
        if(constRz->isChecked())
        {
            // make sure points aren't already there
            for(int i = 0; i < myStructure.loadMat.size(); i++)
            {
                if(forceJointNum==myStructure.loadMat[i][0] && myStructure.loadMat[i][1]==3)
                    repeat = true;
            }

            if(!repeat)
            {
                // add to structure
                forcePoint.push_back(forceJointNum);
                forcePoint.push_back(3);
                forcePoint.push_back(forceDoubleMag);
                myStructure.loadMat.push_back(forcePoint);
                forcePoint.clear();

                numOneClick++;
            }
            else
                numRep++;
        }

        // as long as at least one is unique
        if(numRep!=3)
        {
            // add to undolist, clear redo
            std::string NumForce;
            NumForce = std::to_string(numOneClick);
            std::vector<std::string> oneLine;
            oneLine.push_back("force");
            oneLine.push_back(NumForce);
            undoList.push_back(oneLine);
            redoList.clear();

            // states
            solved = false;
            displace = false;
            setStates();

            // draw
            drawThings();
        }
    }
    catch(std::invalid_argument)
    {
        // message for incorrect input
        QMessageBox noGood;

        noGood.setText("Inputs Incorrect");
        noGood.setInformativeText("please follow example");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::pushButton_setDProperties()
{
    try
    {
        // clear properties from structure
        myStructure.properties.clear();

        // get new properties from toolbar
        QString Estring = addE->text();
        QString Istring = addI->text();
        QString Astring = addA->text();
        QString e1string = adde1->text();
        QString e2string = adde2->text();

        // put new values in structure
        myStructure.properties.push_back(Estring.toDouble());
        myStructure.properties.push_back(Astring.toDouble());
        myStructure.properties.push_back(Istring.toDouble());
        myStructure.properties.push_back(e1string.toDouble());
        myStructure.properties.push_back(e2string.toDouble());

        // clear redo list and tool bars
        redoList.clear();
        clearToolbars();

        // states
        solved = false;
        displace = false;
        setStates();

        // draw things
        drawThings();
    }
    catch(std::invalid_argument)
    {
        // message if incorrect values
        QMessageBox noGood;

        noGood.setText("Inputs Incorrect");
        noGood.setInformativeText("please follow example");
        noGood.setStandardButtons(QMessageBox::Ok);
        noGood.setDefaultButton(QMessageBox::Ok);
        noGood.setWindowTitle("WARNING");
        noGood.exec();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    // accept mouse wheel inputs

    // code on zooming comes from here
    //http://www.qtcentre.org/threads/52603-Zoom-effect-by-mouse-Wheel-in-QGraphicsview

    // set point of scale
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // zoom factor
    double scaleFactor = 1.15;

    // if in or out
    if(event->delta() > 0)
        ui->graphicsView->scale(scaleFactor, scaleFactor);
    else
        ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    // allow scrolling
//    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    ui->graphicsView->verticalScrollBar()->blockSignals(false);
//    ui->graphicsView->horizontalScrollBar()->blockSignals(false);

    std::cout << "WD You Pressed" << std::endl;

//    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *eventRelease)
{
//    // allow scrolling
//    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
//    ui->graphicsView->verticalScrollBar()->blockSignals(true);
//    ui->graphicsView->horizontalScrollBar()->blockSignals(true);

//    // set back to arrow
//    QApplication::setOverrideCursor(Qt::ArrowCursor);

    std::cout << "WD You Released" << std::endl;

    //    eventRelease->accept();
}

void MainWindow::pressThings()
{
    std::cout << "clicked scene" << std::endl;

    // allow scrolling
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->verticalScrollBar()->blockSignals(false);
    ui->graphicsView->horizontalScrollBar()->blockSignals(false);

    // set to hand
    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
}

void MainWindow::releaseThings()
{
    std::cout << "released scene" << std::endl;

    // allow scrolling
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->verticalScrollBar()->blockSignals(true);
    ui->graphicsView->horizontalScrollBar()->blockSignals(true);

    // set back to arrow
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void MainWindow::readFile(std::string fileName)
{
    // number of actions from file
    int numTotalObj = 0;

    // line from text
    std::string line;

    // file to read
    std::ifstream infile (fileName);

    // section counter
    int sections = 0;

    // read until end of file
    while (std::getline(infile,line, '\n'))
    {
        // make sure line isn't blank
        if(line!="")
        {
           // parse the line for the data

                // define vector of strings
                std::vector<std::string> tokens;

                // define delimiters
                std::string delimiters(", ;\t");

                // call tokenize
                tokenize(line, tokens, delimiters);

                if(sections == 0)
                {
                    if(tokens[0] != "joints")  //make sure you haven't reached the next section
                    {
                        // look at what kind of structure is being used
                        myStructure.StructType = tokens[0];
                    }
                }

                if(sections == 1)
                {
                    if(tokens[0] != "members")  //make sure you haven't reached the next section
                    {
                        // add joint coordinates
                        std::vector<double> xSingleJoint;

                        xSingleJoint.push_back(stod(tokens[0]));
                        xSingleJoint.push_back(stod(tokens[1]));

                        // push to structure
                        myStructure.xstruct.push_back(xSingleJoint);

                        // push to undolist
                        std::vector<std::string> oneLine;
                        oneLine.push_back("joint");
                        oneLine.push_back("1");
                        undoList.push_back(oneLine);
                        numTotalObj++;
                    }
                }
                else if(sections == 2)
                {
                    if(tokens[0] != "constraints")  //make sure you haven't reached the next section
                    {
                        // add members to thier joints
                        std::vector<int> xSingleMember;

                        xSingleMember.push_back(stoi(tokens[0]));
                        xSingleMember.push_back(stoi(tokens[1]));

                        // push to structure
                        myStructure.conn.push_back(xSingleMember);

                        // push to undolist
                        std::vector<std::string> oneLine;
                        oneLine.push_back("member");
                        oneLine.push_back("1");
                        undoList.push_back(oneLine);
                        numTotalObj++;
                    }
                }
                else if(sections == 3)
                {
                    if(tokens[0] != "loads")  //make sure you haven't reached the next section
                    {
                        // add constraints
                        std::vector<int> constSingleDOF;

                        constSingleDOF.push_back(stoi(tokens[0]));
                        constSingleDOF.push_back(stoi(tokens[1]));

                        // push to structure
                        myStructure.constMat.push_back(constSingleDOF);

                        // push to undolist
                        std::vector<std::string> oneLine;
                        oneLine.push_back("constraint");
                        oneLine.push_back("1");
                        undoList.push_back(oneLine);
                        numTotalObj++;
                    }
                }
                else if(sections == 4)
                {
                    if(tokens[0] != "properties")  //make sure you haven't reached the next section
                    {
                        // add forces
                        std::vector<double> singleForce;

                        singleForce.push_back(stod(tokens[0]));
                        singleForce.push_back(stod(tokens[1]));
                        singleForce.push_back(stod(tokens[2]));

                        // push to structure
                        myStructure.loadMat.push_back(singleForce);

                        // push to undolist
                        std::vector<std::string> oneLine;
                        oneLine.push_back("force");
                        oneLine.push_back("1");
                        undoList.push_back(oneLine);
                        numTotalObj++;
                    }
                }
                else if(sections == 5)
                {
                    myStructure.properties.push_back(stod(tokens[0]));
                }

                // check what section you are in

                if(tokens[0]=="joints")
                {
                    sections++;
                }
                else if(tokens[0]=="members") // make sure the next section is members
                {
                    sections++;
                }
                else if(tokens[0]=="constraints") // make sure the next section is constraints
                {
                    sections++;
                }
                else if(tokens[0]=="loads") // make sure the next section is loads
                {
                    sections++;
                }
                else if(tokens[0]=="properties") // make sure the next section is properties
                {
                    sections++;
                }
        }
    }

    // push action to undolist
    std::string NumObj;
    NumObj = std::to_string(numTotalObj);
    std::vector<std::string> oneLine;
    oneLine.push_back("file");
    oneLine.push_back(NumObj);
    undoList.push_back(oneLine);
}

void MainWindow::clearToolbars()
{
    // get rid of all tool bars
    // remove from window and delete

    if(jToolBarActive == true)
    {
        this->removeToolBar(jointToolBar);
        jToolBarActive = false;
        delete Title;
        delete XText;
        delete YText;
        delete addJoint;
        delete addXText;
        delete addYText;
        delete jointWidgX;
        delete jointWidgY;
        delete jointToolBar;
    }
    if(mToolBarActive == true)
    {
        this->removeToolBar(memberToolBar);
        mToolBarActive = false;
        delete Title;
        delete FText;
        delete SText;
        delete addMember;
        delete addXText;
        delete addYText;
        delete xLay;
        delete yLay;
        delete jointWidg1;
        delete jointWidg2;
        delete memberToolBar;
    }
    if(cToolBarActive == true)
    {
        this->removeToolBar(constraintToolBar);
        cToolBarActive = false;
        delete Title;
        delete JText;
        delete XText;
        delete YText;
        delete ZText;
        delete addConstraint;
        delete addXText;
        delete constX;
        delete constY;
        delete constRz;
        delete jLay;
        delete fLay;
        delete sLay;
        delete tLay;
        delete jointWidg;
        delete jointWidgX;
        delete jointWidgY;
        delete jointWidgZ;
        delete constraintToolBar;
    }
    if(fToolBarActive == true)
    {
        this->removeToolBar(forceToolBar);
        fToolBarActive = false;
        delete Title;
        delete JText;
        delete MText;
        delete XText;
        delete YText;
        delete ZText;
        delete addForce;
        delete addXText;
        delete addYText;
        delete constX;
        delete constY;
        delete constRz;
        delete jLay;
        delete mLay;
        delete fLay;
        delete sLay;
        delete tLay;
        delete jointWidg;
        delete jointWidgX;
        delete jointWidgY;
        delete momWidg;
        delete magWidg;
        delete forceToolBar;
    }
    if(pToolBarActive == true)
    {
        this->removeToolBar(propToolBar);
        pToolBarActive = false;
        delete setProps;
        delete Title;
        delete EText;
        delete IText;
        delete AText;
        delete e1Text;
        delete e2Text;
        delete addE;
        delete addA;
        delete addI;
        delete adde1;
        delete adde2;
        delete Elay;
        delete Alay;
        delete Ilay;
        delete e1lay;
        delete e2lay;
        delete button;
        delete allProps;
        delete PropWidg;
        delete propToolBar;
    }
    if(sToolBarActive == true)
    {
        this->removeToolBar(stressToolBar);
        sToolBarActive = false;
        delete JText;
        delete sSelect;
        delete jLay;
        delete jointWidg;
        delete stressToolBar;
    }

}

void MainWindow::solveReady()
{
    // check if structure is ready to solve

    if(myStructure.checkReady() && !solved)
        ui->pushButton_solve->setEnabled(true);
    else
        ui->pushButton_solve->setEnabled(false);
}

void MainWindow::setStates()
{
    // set buttons and progress bar based on states
    if(displace)
    {
        ui->pushButton_Disp->setEnabled(false);
        ui->pushButton_Stress->setEnabled(true);
        ui->actionSave_Results->setEnabled(true);
        ui->pushButton_solve->setEnabled(false);
    }
    else if(stress)
    {
        ui->pushButton_Disp->setEnabled(true);
        ui->pushButton_Stress->setEnabled(false);
        ui->actionSave_Results->setEnabled(true);
        ui->pushButton_solve->setEnabled(false);
    }
    else if(solved)
    {
        ui->pushButton_solve->setEnabled(false);
        ui->pushButton_Disp->setEnabled(true);
        ui->pushButton_Stress->setEnabled(true);
        ui->actionSave_Results->setEnabled(true);
    }
    else
    {
        ui->progressBar->setValue(0);
        ui->pushButton_Disp->setEnabled(false);
        ui->pushButton_Stress->setEnabled(false);
        ui->actionSave_Results->setEnabled(false);
    }

    solveReady();
}

QString MainWindow::trimString(std::string reaction)
{
    // trim to sig figs

    // set state
    int numSigFig = 4;
    int numZeros = 0;
    std::string point = ".";
    int posdot = reaction.find(point);

    // if there's a negative sign add on a character to keep
    if(reaction.at(0)=='-')
        numSigFig++;

    // only if string is greater than sig figs
    if(numSigFig < reaction.size())
    {
        // if pos of . is less than sig figs
        if(posdot <= numSigFig)
        {
            // earse up to sig figs
            for(int i = reaction.size(); i >= numSigFig; i--)
            {
                reaction.erase(i);
            }
        }
        else
        {
            // erase up to sig figs
            for(int i = reaction.size(); i >= numSigFig; i--)
            {
                reaction.erase(i);

                if(i<posdot) // count num of trailing zeros needed
                    numZeros++;
            }

            // add trailing zeros
            for(int i = 0; i < numZeros; i++)
                reaction.append("0");
        }
    }

    // convert to QStrings
    QString Qreactions = QString::fromStdString(reaction);

    // return new string
    return Qreactions;
}

void MainWindow::on_actionUndo_triggered()
{
    if(!undoList.empty())
    {
        // get the last action
        std::vector<std::string> lastAction;
        std::string stringNumberOfThings;
        std::string stringTheThing;

        lastAction = undoList.back();

        stringTheThing = lastAction[0];
        stringNumberOfThings = lastAction[1];

        int intNumberOfThings = stoi(stringNumberOfThings);

        // action depends on what was most recent
        if(stringTheThing=="file")
            clearFile(intNumberOfThings);
        else
        {
            // loop through number of things done in action
            for(int i = 0; i < intNumberOfThings; i++)
            {
                if(stringTheThing=="joint")
                    clearJoint();
                else if(stringTheThing=="member")
                    clearMember();
                else if(stringTheThing=="constraint")
                    clearConstraint();
                else if(stringTheThing=="force")
                    clearForce();
            }

            // put action in redo list
            std::vector<std::string> row;
            row.push_back(stringTheThing);
            row.push_back(stringNumberOfThings);
            redoList.push_back(row);

            // remove from end of undolist
            undoList.pop_back();
        }

        // draw to scene
        drawThings();

        // set states
        setStates();
    }
}

void MainWindow::clearJoint()
{
    // push to undid, remove from structure
    undidXStruct.push_back(myStructure.xstruct.back());
    myStructure.xstruct.pop_back();
}

void MainWindow::clearMember()
{
    // push to undid, remove from structure
    undidConn.push_back(myStructure.conn.back());
    myStructure.conn.pop_back();
}

void MainWindow::clearConstraint()
{
    // push to undid, remove from structure
    undidConst.push_back(myStructure.constMat.back());
    myStructure.constMat.pop_back();
}

void MainWindow::clearForce()
{
    // push to undid, remove from structure
    undidLoad.push_back(myStructure.loadMat.back());
    myStructure.loadMat.pop_back();
}

void MainWindow::clearFile(int num)
{
    // remove "file" from undoList
    undoList.pop_back();

    // get actions associated with file
    std::vector<std::string> lastAction;
    std::string stringTheThing;
    std::string stringNumberOfThings;

    for(int i = 0; i < num; i++)
    {
        // get item
        lastAction = undoList.back();
        stringTheThing = lastAction[0];
        stringNumberOfThings = lastAction[1];

        // actions based on undoList item
        if(stringTheThing=="joint")
            clearJoint();
        else if(stringTheThing=="member")
            clearMember();
        else if(stringTheThing=="constraint")
            clearConstraint();
        else if(stringTheThing=="force")
            clearForce();

        // push to redoList
        std::vector<std::string> row;
        row.push_back(stringTheThing);
        row.push_back(stringNumberOfThings);
        redoList.push_back(row);

        // remove from undo List
        undoList.pop_back();
    }

    // push "file" to redo List
    std::vector<std::string> oneLine;
    oneLine.push_back("file");
    oneLine.push_back(std::to_string(num));
    redoList.push_back(oneLine);
}

void MainWindow::on_actionRedo_triggered()
{
    if(!redoList.empty())
    {
        // get action from list
        std::vector<std::string> lastUndidAction;
        std::string stringNumberOfThings;
        std::string stringTheThing;

        lastUndidAction = redoList.back();

        stringTheThing = lastUndidAction[0];
        stringNumberOfThings = lastUndidAction[1];

        int intNumberOfThings = stoi(stringNumberOfThings);

        if(stringTheThing=="file")
            redoFile(intNumberOfThings);
        else
        {
            // loop through number of things in action
            for(int i = 0; i < intNumberOfThings; i++)
            {
                if(stringTheThing=="joint")
                    redoJoint();
                else if(stringTheThing=="member")
                    redoMember();
                else if(stringTheThing=="constraint")
                    redoConstraint();
                else if(stringTheThing=="force")
                    redoForce();
            }

            // put back in undoList
            std::vector<std::string> row;
            row.push_back(stringTheThing);
            row.push_back(stringNumberOfThings);
            undoList.push_back(row);

            // remove from redolist
            redoList.pop_back();
        }
    }

    // draw new things
    drawThings();

    // set states
    setStates();
}

void MainWindow::redoJoint()
{
    // push to structure, remove from undid
    myStructure.xstruct.push_back(undidXStruct.back());
    undidXStruct.pop_back();
}

void MainWindow::redoMember()
{
    // push to structure, remove from undid
    myStructure.conn.push_back(undidConn.back());
    undidConn.pop_back();
}

void MainWindow::redoConstraint()
{
    // push to structure, remove from undid
    myStructure.constMat.push_back(undidConst.back());
    undidConst.pop_back();
}

void MainWindow::redoForce()
{
    // push to structure, remove from undid
    myStructure.loadMat.push_back(undidLoad.back());
    undidLoad.pop_back();
}

void MainWindow::redoFile(int num)
{
    // remove "file" from list
    redoList.pop_back();

    // get next action
    std::vector<std::string> lastAction;
    std::string stringTheThing;
    std::string stringNumberOfThings;

    for(int i = 0; i < num; i++)
    {
        // get nect action
        lastAction = redoList.back();
        stringTheThing = lastAction[0];
        stringNumberOfThings = lastAction[1];

        // action based on type
        if(stringTheThing=="joint")
            redoJoint();
        else if(stringTheThing=="member")
            redoMember();
        else if(stringTheThing=="constraint")
            redoConstraint();
        else if(stringTheThing=="force")
            redoForce();

        // put back in undo list
        std::vector<std::string> row;
        row.push_back(stringTheThing);
        row.push_back(stringNumberOfThings);
        undoList.push_back(row);

        // remove from redo list
        redoList.pop_back();
    }

    // pushback "file" to undo list
    std::vector<std::string> oneLine;
    oneLine.push_back("file");
    oneLine.push_back(std::to_string(num));
    undoList.push_back(oneLine);
}

void MainWindow::drawJNums()
{
    // draw joint number to scene

    // new text deleted when scene cleared

    // clear old jTexts
    jText.clear();

    // repop list
    for(int i = 0; i < myStructure.xstruct.size(); i++)
    {
        // new text item to list
        QString jointNumb = QString::fromStdString(std::to_string(i+1));

        QGraphicsTextItem *newText = new QGraphicsTextItem;
        newText->setDefaultTextColor(Qt::cyan);
        newText->setPos(myStructure.xstruct[i][0],-myStructure.xstruct[i][1]);
        newText->setPlainText(jointNumb);
        jText.push_back(newText);
    }

    // draw joint numbers
    for(int i = 0; i < jText.size(); i++)
        scene->addItem(jText[i]);
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "CS clicked scene" << std::endl;

    // allow scrolling
//    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    ui->graphicsView->verticalScrollBar()->blockSignals(false);
//    ui->graphicsView->horizontalScrollBar()->blockSignals(false);

//    // set to hand
//    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "CS released scene" << std::endl;

//    // allow scrolling
//    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
//    ui->graphicsView->verticalScrollBar()->blockSignals(true);
//    ui->graphicsView->horizontalScrollBar()->blockSignals(true);

//    // set back to arrow
//    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About","DynoSim is a state of the art \n Structural Simulation Package \n"
                                    "IT HAS AN UNDO BUTTON");
}

void MainWindow::on_actionHelp_Document_triggered()
{
    QString fileName1 = "helpDoc.txt";
    QFile file1(fileName1);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

//    // show the directory path of opened file
//    dir->setText(QFileInfo(file1).dir().path());

    QTextBrowser *b = new QTextBrowser;
    b->setText(file1.readAll());
    b->show();
}
