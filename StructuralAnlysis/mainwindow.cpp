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

// to DO //////////////
// user select joints
// zoom and pan
// stop leaking text memory
// if already exists
// list nodes
// heads out on forces
// when you click to add something else revert to needing to solve
// ////////////////////

// global variables
static Analyze myStructure;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showMaximized();

    solved = false;
    displace = false;
    constraint = false;
    force = false;
    jToolBarActive = false;
    mToolBarActive = false;
    cToolBarActive = false;
    fToolBarActive = false;
    pToolBarActive = false;

    // set up graphics scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

    // get file name
    QString fileNameQ = QFileDialog::getOpenFileName(this,"Open Shape File", "","*.txt");
    std::string fileName = fileNameQ.toStdString();

//    std::string fileName = "C:\\Users\\Spencer\\Documents\\570project\\build-StructuralAnlysis-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\StructureInput.txt";

    // check file for errors

    try
    {
        readFile(fileName);

        zoom = 1;

        drawMembers();
        drawJoint();
    }
    catch(std::invalid_argument)
    {
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
    int i = 0;
    std::string outPutFile = "ResultsFile0.txt";
    bool fileExists = true;

    // find next file name available
    while(fileExists)
    {
        i++;
        outPutFile = outPutFile.substr(0,outPutFile.size()-5);
        outPutFile.append(std::to_string(i));
        outPutFile.append(".txt");

        std::ifstream testFile(outPutFile);

        if(!testFile)
            fileExists = false;
    }

    std::ofstream solOutPut;
    solOutPut.open(outPutFile);

    // loop through displacements
    for(int i = 0; i < myStructure.dxstruct.size(); i++)
    {
        solOutPut << "Joint " << std::to_string(i+1) << "\t"
                  << "dX = " << std::to_string(myStructure.dxstruct[i][0]) << "\t"
                  << "dY = " << std::to_string(myStructure.dxstruct[i][1]) << std::endl;
    }

    // loop through member reactions
    for(int i = 0; i < myStructure.rmem.size(); i++)
    {
        solOutPut << "Member " << std::to_string(i+1) << "\t"
                  << "Axial 1 = " << std::to_string(myStructure.rmem[i][0]) << "\t"
                  << "Shear 1 = " << std::to_string(myStructure.rmem[i][1]) << "\t"
                  << "Moment 1 = " << std::to_string(myStructure.rmem[i][2]) << "\t"
                  << "Axial 2 = " << std::to_string(myStructure.rmem[i][3]) << "\t"
                  << "Shear 2 = " << std::to_string(myStructure.rmem[i][4]) << "\t"
                  << "Moment 2 = " << std::to_string(myStructure.rmem[i][5]) << std::endl;
    }

    solOutPut.close();

}

void MainWindow::on_actionClear_triggered()
{

    QMessageBox sure;

    sure.setText("Are you sure you want to clear?");
    sure.setInformativeText("You may not undo this action.");
    sure.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    sure.setDefaultButton(QMessageBox::Cancel);
    sure.setWindowTitle("WARNING");
    int ret = sure.exec();

    switch (ret) {
    case QMessageBox::Ok:

        // clear the screan
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

        solved = false;
        displace = false;
        constraint = false;
        force = false;
        jToolBarActive = false;
        mToolBarActive = false;
        cToolBarActive = false;
        fToolBarActive = false;
        pToolBarActive = false;

        ui->pushButton_Disp->setEnabled(false);
        ui->pushButton_Stress->setEnabled(false);
        ui->pushButton_solve->setEnabled(false);

        break;
    case QMessageBox::Cancel:
        break;

    default:
        break;
    }

}

void MainWindow::on_actionJoints_triggered()
{
    clearToolbars();

    jToolBarActive = true;

    // create toolbar
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
    clearToolbars();

    mToolBarActive = true;

    // create toolbar
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

    clearToolbars();

    cToolBarActive = true;

    // create toolbar
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
    clearToolbars();

    fToolBarActive = true;

    // create toolbar
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
    clearToolbars();

    pToolBarActive = true;

    // create toolbar
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
    if(solved == false)
    {
        undoList.clear();

        myStructure.preprocessing();
        myStructure.AssembleStructStiff();
        myStructure.Triangularization();
        myStructure.AssembleStructForce();
        myStructure.BackSub();
        myStructure.postprocessing();

        dDeform = 1;

        ui->pushButton_solve->setEnabled(false);
        ui->pushButton_Disp->setEnabled(true);
        ui->pushButton_Stress->setEnabled(true);

        solved = true;
    }
}

void MainWindow::on_pushButton_Disp_released()
{
    if(solved==true)
    {
        if(displace == false)
        {
            displace = true;

            drawDStructure();

            if(force == true)
            {
                drawForces();
            }
        }
        else if(displace == true)
        {
            displace = false;

            scene->clear();         

            if(constraint == true)
            {
                drawConstraints();
            }

            drawMembers();
            drawJoint();

            if(force == true)
            {
                drawForces();
            }
        }
    }
}

void MainWindow::on_horizontalSlider_scaleDisp_sliderMoved(int position)
{
    if(solved==true)
    {
        dDeform = 1;
        dDeform*=position;

        //drawStructure();
        if(displace==true)
        {
            if(constraint==true)
            {
                drawConstraints();
            }
            drawDStructure();
            if(force==true)
            {
                drawForces();
            }

        }
    }
}

void MainWindow::on_pushButton_Stress_released()
{

}

void MainWindow::on_checkBox_const_toggled(bool checked)
{
    if(checked==true)
    {
        constraint = true;

        scene->clear();
        drawConstraints();

        // redraw other options if there
        if(displace == true)
        {
            drawDStructure();
        }
        else
        {
           drawMembers();
           drawJoint();
        }
        if(force == true)
        {
            drawForces();
        }
    }
    else
    {
        constraint = false;
        scene->clear();

        // redraw other options if there
        if(displace == true)
        {
            drawDStructure();
        }
        else
        {
           drawMembers();
           drawJoint();
        }
        if(force == true)
        {
            drawForces();
        }
    }


}

void MainWindow::on_checkBox_Force_toggled(bool checked)
{

    if(checked==true)
    {
        force = true;
        drawForces();
    }
    else
    {
        force = false;
        scene->clear();

        // redraw other options if there
        if(constraint == true)
        {
            drawConstraints();
        }
        if(displace == true)
        {
            drawDStructure();
        }
        else
        {
            drawMembers();
            drawJoint();
        }
    }
}

void MainWindow::drawJoint()
{
    QBrush jgrey(Qt::gray);
    QPen jPen(Qt::white);

    for(int i = 0; i < myStructure.xstruct.size(); i++)
    {
        scene->addEllipse(myStructure.xstruct[i][0]-5,-myStructure.xstruct[i][1]-5,10,10,jPen,jgrey);
    }
}

void MainWindow::drawMembers()
{
    QPen mPen;

    if(displace==true)
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

    for(uint i = 0; i < myStructure.conn.size(); i++)
    {
        int One = myStructure.conn[i][0];
        int Two = myStructure.conn[i][1];

        double x1 = myStructure.xstruct[One-1][0];
        double y1 = -myStructure.xstruct[One-1][1];
        double x2 = myStructure.xstruct[Two-1][0];
        double y2 = -myStructure.xstruct[Two-1][1];

        scene->addLine(x1,y1,x2,y2,mPen);
    }
}

void MainWindow::drawConstraints()
{
    QBrush constBrush(Qt::blue);
    QPen constPen(Qt::blue);
    constPen.setWidth(2);

    // loop through constraint matrix
    for(uint i = 0; i < myStructure.constMat.size(); i++)
    {
        int m = myStructure.constMat[i][0]-1;
        int dir = myStructure.constMat[i][1];

        double x1 = myStructure.xstruct[m][0];
        double y1 = -myStructure.xstruct[m][1];

        if(dir==1)
        {
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-30,y1-15) << QPointF(x1-30,y1+15);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,constPen,constBrush);
        }
        else if(dir==2)
        {
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-15,y1+30) << QPointF(x1+15,y1+30);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,constPen,constBrush);
        }
        else
        {
            noDrawnRot = scene->addRect(x1-10,y1-10,20,20,constPen,constBrush);
        }

    }
}

void MainWindow::drawForces()
{
    for(int i = myText.size()-1; i >= 0; i--)
    //    delete myText[i];
    myText.clear();

    QBrush momBrush(Qt::transparent);
    QBrush momBrush2(Qt::yellow);
    QBrush loadBrush(Qt::green);
    QPen loadPen(Qt::green);
    QPen momPen(Qt::yellow);
    loadPen.setWidth(1);
    momPen.setWidth(3);
    bool negative = false;

    // loop through constraint matrix
    for(uint i = 0; i < myStructure.loadMat.size(); i++)
    {
        int m = (int)myStructure.loadMat[i][0]-1;
        int dir = (int)myStructure.loadMat[i][1];
        std::string forceMag = std::to_string(myStructure.loadMat[i][2]);

        // get rid of trailing zeros
        std::string point = ".";
        int posdot = forceMag.find(point);
        int strSize = forceMag.size();

        bool nonZero = false;

        if(posdot < strSize)
        {
            for(int j = strSize; j >= posdot-1; j--)
            {
                if(forceMag.substr(j-1,1)=="0" || forceMag.substr(j,1)==".")
                {
                    if(nonZero==false)
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

        QString forceT = QString::fromStdString(forceMag);
        if(forceT.at(0)=='-')
        {
            forceT.remove(0,1);
            negative = true;
        }

        // create new text item
        QGraphicsTextItem *newText = new QGraphicsTextItem;

        newText->setDefaultTextColor(Qt::white);
        newText->setPlainText(forceT);

        double x1 = myStructure.xstruct[m][0];
        double y1 = -myStructure.xstruct[m][1];

        if(dir==1)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1-50,y1,loadPen);
            noDrawnTransShape.clear();

            // draw triangle
            if(negative==true)
            {
                noDrawnTransShape << QPointF(x1-50,y1) << QPointF(x1-30,y1+5) << QPointF(x1-30,y1-5);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                newText->setX(x1-80);
                newText->setY(y1);

                // reset negative
                negative = false;
            }
            else
            {
                noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-20,y1+5) << QPointF(x1-20,y1-5);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                newText->setX(x1-80);
                newText->setY(y1);
            }
        }
        else if(dir==2)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1,y1-50,loadPen);
            noDrawnTransShape.clear();

            if(negative == true)
            {
                // draw triangle
                noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-5,y1-20) << QPointF(x1+5,y1-20);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                newText->setX(x1+5);
                newText->setY(y1-50);

                // reset negative
                negative = false;
            }
            else
            {
                // draw triangle
                noDrawnTransShape << QPointF(x1,y1-50) << QPointF(x1-5,y1-30) << QPointF(x1+5,y1-30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

                newText->setX(x1+5);
                newText->setY(y1-25);
            }
        }
        else
        {
            myStructCirc = scene->addEllipse(x1-20, y1-20, 40, 40, momPen, momBrush);
            noDrawnTransShape.clear();

            if(negative == true)
            {
                // draw triangle
                noDrawnTransShape << QPointF(x1+10,y1-20) << QPointF(x1-10,y1-10) << QPointF(x1-10,y1-30);
                noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);

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

                newText->setX(x1-25);
                newText->setY(y1-60);
            }
        }

        myText.push_back(newText);
    }

    // loop through my Text
    for(int i = 0; i < myText.size(); i++)
        scene->addItem(myText[i]);
}

void MainWindow::drawDStructure()
{
    // clear gview
    scene->clear();

    if(constraint == true)
    {
        drawConstraints();
    }

    drawMembers();
    drawJoint();

    double x1;
    double y1;
    double x2;
    double y2;

    for(uint i = 0; i < myStructure.conn.size();i++)
    {

        // draw with delta
        int m = myStructure.conn[i][0]-1;
        int n = myStructure.conn[i][1]-1;

        x1 = (myStructure.xstruct[m][0]+myStructure.dxstruct[m][0]*dDeform);
        y1 = -(myStructure.xstruct[m][1]+myStructure.dxstruct[m][1]*dDeform);
        x2 = (myStructure.xstruct[n][0]+myStructure.dxstruct[n][0]*dDeform);
        y2 = -(myStructure.xstruct[n][1]+myStructure.dxstruct[n][1]*dDeform);

        QPen linePen(Qt::red);
        linePen.setWidth(5);

        myStrucLine = scene->addLine(x1,y1,x2,y2,linePen);
    }
}

void MainWindow::pushButton_addJoint()
{
    try
    {
        std::vector<double> jPoints;

        QString myX = addXText->text();
        QString myY = addYText->text();

        double x = myX.toDouble();
        double y = myY.toDouble();

        jPoints.push_back(x);
        jPoints.push_back(y);

        myStructure.xstruct.push_back(jPoints);

        drawJoint();

        std::vector<std::string> oneLine;
        oneLine.push_back("joint");
        oneLine.push_back("1");
        undoList.push_back(oneLine);
    }
    catch(std::invalid_argument)
    {
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
        std::vector<int> mPoints;

       QString myOne = addXText->text();
       QString myTwo = addYText->text();

       int One = myOne.toInt();
       int Two = myTwo.toInt();

       mPoints.push_back(One);
       mPoints.push_back(Two);

       myStructure.conn.push_back(mPoints);

       drawMembers();
       drawJoint();

       std::vector<std::string> oneLine;
       oneLine.push_back("member");
       oneLine.push_back("1");
       undoList.push_back(oneLine);
    }
    catch(std::invalid_argument)
    {
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
        int numOneClick = 0;

        std::vector<int> constPoint;

        QString constJoint = addXText->text();

        int constJointNum = constJoint.toInt();

        if(constX->isChecked())
        {
            constPoint.push_back(constJointNum);
            constPoint.push_back(1);
            myStructure.constMat.push_back(constPoint);
            constPoint.clear();

            numOneClick++;
        }
        if(constY->isChecked())
        {
            constPoint.push_back(constJointNum);
            constPoint.push_back(2);
            myStructure.constMat.push_back(constPoint);
            constPoint.clear();

            numOneClick++;
        }
        if(constRz->isChecked())
        {
            constPoint.push_back(constJointNum);
            constPoint.push_back(3);
            myStructure.constMat.push_back(constPoint);
            constPoint.clear();

            numOneClick++;
        }

        std::string NumConst;
        NumConst = std::to_string(numOneClick);
        std::vector<std::string> oneLine;
        oneLine.push_back("constraint");
        oneLine.push_back(NumConst);
        undoList.push_back(oneLine);

        drawConstraints();
        drawMembers();
        drawJoint();
    }
    catch(std::invalid_argument)
    {
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
        int numOneClick = 0;

        std::vector<double> forcePoint;

        QString forceJoint = addXText->text();
        QString forceMag = addYText->text();

        double forceJointNum = forceJoint.toInt();
        double forceDoubleMag = forceMag.toDouble();

        if(constX->isChecked())
        {
            forcePoint.push_back(forceJointNum);
            forcePoint.push_back(1);
            forcePoint.push_back(forceDoubleMag);
            myStructure.loadMat.push_back(forcePoint);
            forcePoint.clear();

            numOneClick++;
        }
        if(constY->isChecked())
        {
            forcePoint.push_back(forceJointNum);
            forcePoint.push_back(2);
            forcePoint.push_back(forceDoubleMag);
            myStructure.loadMat.push_back(forcePoint);
            forcePoint.clear();

            numOneClick++;
        }
        if(constRz->isChecked())
        {
            forcePoint.push_back(forceJointNum);
            forcePoint.push_back(3);
            forcePoint.push_back(forceDoubleMag);
            myStructure.loadMat.push_back(forcePoint);
            forcePoint.clear();

            numOneClick++;
        }

        std::string NumForce;
        NumForce = std::to_string(numOneClick);
        std::vector<std::string> oneLine;
        oneLine.push_back("force");
        oneLine.push_back(NumForce);
        undoList.push_back(oneLine);

        drawConstraints();
        drawMembers();
        drawJoint();
        drawForces();
    }
    catch(std::invalid_argument)
    {
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
        myStructure.properties.clear();

        QString Estring = addE->text();
        QString Istring = addI->text();
        QString Astring = addA->text();
        QString e1string = adde1->text();
        QString e2string = adde2->text();

        myStructure.properties.push_back(Estring.toDouble());
        myStructure.properties.push_back(Astring.toDouble());
        myStructure.properties.push_back(Istring.toDouble());
        myStructure.properties.push_back(e1string.toDouble());
        myStructure.properties.push_back(e2string.toDouble());

        clearToolbars();
        solveReady();
    }
    catch(std::invalid_argument)
    {
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
    // test
    std::cout << "You Scrolled the Wheel ";

    QPoint numDegrees = event->angleDelta() / 8;
    QPoint numSteps = numDegrees / 15;
    QPoint mousePos = event->pos();

    double myZoomY = numSteps.y();
    double myPosX = mousePos.x();
    double myPosY = mousePos.y();

    std::cout << "to Position: y = "<< myZoomY << std::endl;
    std::cout << "The mouse position is: x = " << myPosX << " y = " << myPosY << std::endl;

    // zoom depending on sign of y
    if(myZoomY < 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }

    event->accept();
}

void MainWindow::zoomIn()
{
    if(zoom >= 1)
    {   // clear the scene of the lines
        scene->clear();

        // set new zoom factor
        zoom++;

        // draw the shapes again
        if(displace == true)
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawDStructure();

            if(force == true)
            {
                drawForces();
            }
        }
        else
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawMembers();
            drawJoint();

            if(force == true)
            {
                drawForces();
            }
        }
    }
    else if(zoom < 1)
    {
        // clear the scene of the lines
        scene->clear();

        zoom = zoom + 0.1;

        // draw the shapes again
        if(displace == true)
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawDStructure();

            if(force == true)
            {
                drawForces();
            }
        }
        else
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawMembers();
            drawJoint();

            if(force == true)
            {
                drawForces();
            }
        }
    }
}

void MainWindow::zoomOut()
{
    if(zoom > 1)
    {
        // clear the scene of the lines
        scene->clear();

        // set new zoom factor
        zoom--;

        // draw the shapes again
        if(displace == true)
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawDStructure();

            if(force == true)
            {
                drawForces();
            }
        }
        else
        {
            if(constraint == true)
            {
                drawConstraints();
            }

            drawMembers();
            drawJoint();

            if(force == true)
            {
                drawForces();
            }
        }
    }
    else if(zoom <= 1)
    {
        if(zoom > .1)
        {
            // clear the scene of the lines
            scene->clear();

            zoom = zoom - 0.1;

            // draw the shapes again
            if(displace == true)
            {
                if(constraint == true)
                {
                    drawConstraints();
                }

                drawDStructure();

                if(force == true)
                {
                    drawForces();
                }
            }
            else
            {
                if(constraint == true)
                {
                    drawConstraints();
                }

                drawMembers();
                drawJoint();

                if(force == true)
                {
                    drawForces();
                }
            }
        }
    }
}

void MainWindow::readFile(std::string fileName)
{
    // read file
    int numTotalObj = 0;

    std::string line;
    std::ifstream infile (fileName);
    int sections = 0;

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

                            myStructure.xstruct.push_back(xSingleJoint);

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

                        myStructure.conn.push_back(xSingleMember);

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
                        std::vector<int> constSingleDOF;

                        constSingleDOF.push_back(stoi(tokens[0]));
                        constSingleDOF.push_back(stoi(tokens[1]));

                        myStructure.constMat.push_back(constSingleDOF);

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
                        std::vector<double> singleForce;

                        singleForce.push_back(stod(tokens[0]));
                        singleForce.push_back(stod(tokens[1]));
                        singleForce.push_back(stod(tokens[2]));

                        myStructure.loadMat.push_back(singleForce);

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

    std::string NumObj;
    NumObj = std::to_string(numTotalObj);
    std::vector<std::string> oneLine;
    oneLine.push_back("file");
    oneLine.push_back(NumObj);
    undoList.push_back(oneLine);

    ui->pushButton_solve->setEnabled(true);
}

void MainWindow::clearToolbars()
{
    // get rid of all tool bars
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

}

void MainWindow::solveReady()
{
    if(myStructure.checkReady()==true)
        ui->pushButton_solve->setEnabled(true);
}

void MainWindow::on_actionUndo_triggered()
{
    if(!undoList.empty())
    {
        std::vector<std::string> lastAction;
        std::string stringNumberOfThings;
        std::string stringTheThing;

        lastAction = undoList.back();

        stringTheThing = lastAction[0];
        stringNumberOfThings = lastAction[1];

        int intNumberOfThings = stoi(stringNumberOfThings);

        if(stringTheThing=="file")
        {
            clearFile(intNumberOfThings);
        }
        else
        {
            for(int i = 0; i < intNumberOfThings; i++)
            {
                if(stringTheThing=="joint")
                {
                    clearJoint();
                }
                else if(stringTheThing=="member")
                {
                    clearMember();
                }
                else if(stringTheThing=="constraint")
                {
                    clearConstraint();
                }
                else if(stringTheThing=="force")
                {
                    clearForce();
                }
            }

            std::vector<std::string> row;
            row.push_back(stringTheThing);
            row.push_back(stringNumberOfThings);
            redoList.push_back(row);

            undoList.pop_back();
        }

        clearDraw();
    }
}

void MainWindow::clearJoint()
{
    undidXStruct.push_back(myStructure.xstruct.back());
    myStructure.xstruct.pop_back();
}

void MainWindow::clearMember()
{
    undidConn.push_back(myStructure.conn.back());
    myStructure.conn.pop_back();
}

void MainWindow::clearConstraint()
{
    undidConst.push_back(myStructure.constMat.back());
    myStructure.constMat.pop_back();
}

void MainWindow::clearForce()
{
    undidLoad.push_back(myStructure.loadMat.back());
    myStructure.loadMat.pop_back();
}

void MainWindow::clearFile(int num)
{
    undoList.pop_back();

    std::vector<std::string> lastAction;
    std::string stringTheThing;

    for(int i = 0; i < num; i++)
    {
        lastAction = undoList.back();
        stringTheThing = lastAction[0];

        if(stringTheThing=="joint")
            clearJoint();
        else if(stringTheThing=="member")
            clearMember();
        else if(stringTheThing=="constraint")
            clearConstraint();
        else if(stringTheThing=="force")
            clearForce();

        undoList.pop_back();
    }
}

void MainWindow::clearDraw()
{
    scene->clear();

    if(constraint == true)
    {
        drawConstraints();
    }

    drawMembers();
    drawJoint();

    if(force == true)
    {
        drawForces();
    }

    if(displace==true)
        drawDStructure();
}

void MainWindow::on_actionRedo_triggered()
{
    if(!redoList.empty())
    {
        std::vector<std::string> lastUndidAction;
        std::string stringNumberOfThings;
        std::string stringTheThing;

        lastUndidAction = redoList.back();

        stringTheThing = lastUndidAction[0];
        stringNumberOfThings = lastUndidAction[1];

        int intNumberOfThings = stoi(stringNumberOfThings);

        for(int i = 0; i < intNumberOfThings; i++)
        {
            if(stringTheThing=="joint")
            {
                redoJoint();
            }
            else if(stringTheThing=="member")
            {
                redoMember();
            }
            else if(stringTheThing=="constraint")
            {
                redoConstraint();
            }
            else if(stringTheThing=="force")
            {
                redoForce();
            }
        }

        std::vector<std::string> row;
        row.push_back(stringTheThing);
        row.push_back(stringNumberOfThings);
        undoList.push_back(row);

        redoList.pop_back();
    }

    clearDraw();
}

void MainWindow::redoJoint()
{
    myStructure.xstruct.push_back(undidXStruct.back());
    undidXStruct.pop_back();
}

void MainWindow::redoMember()
{
    myStructure.conn.push_back(undidConn.back());
    undidConn.pop_back();
}

void MainWindow::redoConstraint()
{
    myStructure.constMat.push_back(undidConst.back());
    undidConst.pop_back();
}

void MainWindow::redoForce()
{
    myStructure.loadMat.push_back(undidLoad.back());
    undidLoad.pop_back();
}
