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

// global variables
static Analyze myStructure;
static Analyze myDrawnStructure;
QPointF myCenter;

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

    readFile(fileName);

    zoom = 3;

    // draw structure
    drawStructure();

    myCenter.setX((xmax-xmin)/2);
    myCenter.setY((ymax-ymin)/2);

    ui->graphicsView->centerOn(myCenter);
}

void MainWindow::on_actionSave_Results_triggered()
{
    // write results to file
}

void MainWindow::readFile(std::string fileName)
{
    // read file

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

                // find # of elements in vector
                int s = tokens.size();

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

   ui->pushButton_solve->setEnabled(true);
}

void MainWindow::drawStructure()
{
    double x1;
    double y1;
    double x2;
    double y2;

    // draw a line for each member
    for(uint i = 0; i < myStructure.conn.size();i++)
    {
        // get x and y coordinates

        int m = myStructure.conn[i][0]-1;
        int n = myStructure.conn[i][1]-1;

        x1 = myStructure.xstruct[m][0]*zoom;
        y1 = -myStructure.xstruct[m][1]*zoom;
        x2 = myStructure.xstruct[n][0]*zoom;
        y2 = -myStructure.xstruct[n][1]*zoom;

        if(i == 0)
        {
            xmin = x1;
            xmax = x1;
            ymin = y1;
            ymax = y1;
        }
        if(x1 > xmax)
            xmax = x1;
        if(x2 > xmax)
            xmax = x2;
        if(y1 > ymax)
            ymax = y1;
        if(y2 > ymax)
            ymax = y2;
        if(x1 < xmin)
            xmin = x1;
        if(x2 < xmin)
            xmin = x2;
        if(y1 < ymin)
            ymin = y1;
        if(y2 < ymin)
            ymin = y2;


        QPen linePen(Qt::white);
        linePen.setWidth(5);

        myStrucLine = scene->addLine(x1,y1,x2,y2,linePen);

    }
}

void MainWindow::drawDStructure()
{
    // clear gview
    scene->clear();

    drawStructure();

    double x1;
    double y1;
    double x2;
    double y2;

    for(uint i = 0; i < myStructure.conn.size();i++)
    {

        // draw with delta
        int m = myStructure.conn[i][0]-1;
        int n = myStructure.conn[i][1]-1;

        x1 = (myStructure.xstruct[m][0]+myStructure.dxstruct[m][0]*dDeform)*zoom;
        y1 = -(myStructure.xstruct[m][1]+myStructure.dxstruct[m][1]*dDeform)*zoom;
        x2 = (myStructure.xstruct[n][0]+myStructure.dxstruct[n][0]*dDeform)*zoom;
        y2 = -(myStructure.xstruct[n][1]+myStructure.dxstruct[n][1]*dDeform)*zoom;

        if(i == 0)
        {
            xmin = x1;
            xmax = x1;
            ymin = y1;
            ymax = y1;
        }
        if(x1 > xmax)
            xmax = x1;
        if(x2 > xmax)
            xmax = x2;
        if(y1 > ymax)
            ymax = y1;
        if(y2 > ymax)
            ymax = y2;
        if(x1 < xmin)
            xmin = x1;
        if(x2 < xmin)
            xmin = x2;
        if(y1 < ymin)
            ymin = y1;
        if(y2 < ymin)
            ymin = y2;

        QPen linePen(Qt::red);
        linePen.setWidth(5);

        myStrucLine = scene->addLine(x1,y1,x2,y2,linePen);
    }
}

void MainWindow::on_actionClear_triggered()
{
    // clear the screan
    scene->clear();

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
}

void MainWindow::on_pushButton_solve_released()
{
    if(solved == false)
    {
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

void MainWindow::on_horizontalSlider_scaleDisp_sliderMoved(int position)
{
    if(solved==true)
    {
        dDeform = 1;
        dDeform*=position;

        //drawStructure();
        if(displace==true)
        {
            drawDStructure();

            if(constraint==true)
            {
                drawConstraints();
            }
            if(force==true)
            {
                drawForces();
            }

        }
    }
}

void MainWindow::drawConstraints()
{
    QBrush constBrush(Qt::blue);
    QPen constPen(Qt::black);
    constPen.setWidth(2);

    // loop through constraint matrix
    for(uint i = 0; i < myStructure.constMat.size(); i++)
    {
        int m = myStructure.constMat[i][0]-1;
        int dir = myStructure.constMat[i][1];

        double x1 = myStructure.xstruct[m][0]*zoom;
        double y1 = -myStructure.xstruct[m][1]*zoom;

        if(dir==1)
        {
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-10*zoom,y1-5*zoom) << QPointF(x1-10*zoom,y1+5*zoom);
            noTrans = scene->addPolygon(noTransShape,constPen,constBrush);
        }
        else if(dir==2)
        {
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-5*zoom,y1+10*zoom) << QPointF(x1+5*zoom,y1+10*zoom);
            noTrans = scene->addPolygon(noTransShape,constPen,constBrush);
        }
        else
        {
            noRot = scene->addRect(x1-5*zoom,y1-5*zoom,10*zoom,10*zoom,constPen,constBrush);
        }

    }
}

void MainWindow::drawForces()
{
    QBrush momBrush(Qt::transparent);
    QBrush momBrush2(Qt::yellow);
    QBrush loadBrush(Qt::green);
    QPen loadPen(Qt::green);
    QPen momPen(Qt::yellow);
    loadPen.setWidth(1);
    momPen.setWidth(3);

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

        double x1 = myStructure.xstruct[m][0]*zoom;
        double y1 = -myStructure.xstruct[m][1]*zoom;

        myText = new QGraphicsTextItem(forceT);
        myText->setDefaultTextColor(Qt::white);

        if(dir==1)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1-30*zoom,y1,loadPen);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-10*zoom,y1+5*zoom) << QPointF(x1-10*zoom,y1-5*zoom);
            noTrans = scene->addPolygon(noTransShape,loadPen,loadBrush);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1-40*zoom);
            myText->setY(y1-10*zoom);

            scene->addItem(myText);

        }
        else if(dir==2)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1,y1-30*zoom,loadPen);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-5*zoom,y1-10*zoom) << QPointF(x1+5*zoom,y1-10*zoom);
            noTrans = scene->addPolygon(noTransShape,loadPen,loadBrush);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1+5*zoom);
            myText->setY(y1-10*zoom);

            scene->addItem(myText);

        }
        else
        {
            myStructCirc = scene->addEllipse(x1-10*zoom, y1-10*zoom, 20*zoom, 20*zoom,momPen,momBrush);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1+2,y1-10*zoom) << QPointF(x1-3*zoom,y1-6*zoom) << QPointF(x1-3*zoom,y1-14*zoom);
            noTrans = scene->addPolygon(noTransShape,momPen,momBrush2);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1-10*zoom);
            myText->setY(y1-30*zoom);

            scene->addItem(myText);
        }
    }
}

void MainWindow::on_pushButton_Disp_released()
{
    if(solved==true)
    {
        if(displace == false)
        {

            drawDStructure();

            if(constraint == true)
            {
                drawConstraints();
            }
            if(force == true)
            {
                drawForces();
            }
        }
        if(displace == true)
        {

            scene->clear();
            drawStructure();

            if(constraint == true)
            {
                drawConstraints();
            }
            if(force == true)
            {
                drawForces();
            }
        }

        // switch displace
        if(displace==true)
            displace=false;
        else
            displace=true;
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
        drawConstraints();
    }
    else
    {
        constraint = false;
        scene->clear();
        drawStructure();

        // redraw other options if there
        if(displace == true)
        {
            drawDStructure();
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
        drawStructure();

        // redraw other options if there
        if(displace == true)
        {
            drawDStructure();
        }
        if(constraint == true)
        {
            drawConstraints();
        }
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

    myCenter.setX(myPosX);
    myCenter.setY(myPosY);

    // zoom depending on sign of y
    if(myZoomY < 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }

    ui->graphicsView->centerOn(myCenter);

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
        if(solved == true)
        {
            drawStructure();
        }
        else
        {
            drawStructure();
        }
    }
    else if(zoom < 1)
    {
        // clear the scene of the lines
        scene->clear();

        zoom = zoom + 0.1;

        // draw the shapes again
        if(solved == true)
        {
            drawStructure();
        }
        else
        {
            drawStructure();
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
        if(solved == true)
        {
            drawStructure();
        }
        else
        {
            drawStructure();
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
            if(solved == true)
            {

            }
            else
            {
                drawStructure();
            }
        }
    }
}

void MainWindow::on_actionJoints_triggered()
{
    clearToolbars();

    jToolBarActive = true;

    // create toolbar
    jointToolBar = new QToolBar("Place Joints");
    QWidget *jointWidgX = new QWidget;
    QWidget *jointWidgY = new QWidget;

    jointToolBar->isMovable();

    // add labels
    QLabel *Title = new QLabel("Insert Joints");
    QLabel *XText = new QLabel("X:");
    QLabel *YText = new QLabel("Y:");

    // insert button
    addJoint = new QPushButton("ADD");

    addXText = new QLineEdit;
    addYText = new QLineEdit;

    // add layouts
    QHBoxLayout *xLay = new QHBoxLayout();
    xLay->addWidget(XText);
    xLay->addWidget(addXText);

    QHBoxLayout *yLay = new QHBoxLayout();
    yLay->addWidget(YText);
    yLay->addWidget(addYText);

    jointToolBar->addWidget(Title);
    jointToolBar->addSeparator();

    jointWidgX->setLayout(xLay);
    jointWidgY->setLayout(yLay);

    jointToolBar->addWidget(jointWidgX);
    jointToolBar->addWidget(jointWidgY);

    jointToolBar->addWidget(addJoint);

    this->addToolBar(jointToolBar);

    connect(addJoint,SIGNAL(clicked()),this,SLOT(on_pushButton_addJoint_released()));

}

void MainWindow::on_pushButton_addJoint_released()
{
    std::vector<double> jPoints;

    QString myX = addXText->text();
    QString myY = addYText->text();

    double x = myX.toDouble();
    double y = myY.toDouble();

    jPoints.push_back(x);
    jPoints.push_back(y);

    myStructure.xstruct.push_back(jPoints);

    QGraphicsEllipseItem *newJoint = new QGraphicsEllipseItem;

    drawnJoints.push_back(newJoint);

    drawJoint();
}

void MainWindow::drawJoint()
{
    QBrush jgrey(Qt::gray);
    QPen jPen(Qt::white);

    for(int i = 0; i < drawnJoints.size(); i++)
    {
        drawnJoints[i] = scene->addEllipse(myStructure.xstruct[i][0]-5,-myStructure.xstruct[i][1]-5,10,10,jPen,jgrey);
    }
}

void MainWindow::drawMembers()
{
    QPen mWhite(Qt::white);
    mWhite.setWidth(5);

    for(int i = 0; i < drawnMembers.size(); i++)
    {
        int One = myStructure.conn[i][0];
        int Two = myStructure.conn[i][1];

        double x1 = myStructure.xstruct[One-1][0];
        double y1 = -myStructure.xstruct[One-1][1];
        double x2 = myStructure.xstruct[Two-1][0];
        double y2 = -myStructure.xstruct[Two-1][1];

        drawnMembers[i] = scene->addLine(x1,y1,x2,y2,mWhite);
    }
}



void MainWindow::on_actionMembers_triggered()
{
    clearToolbars();

    mToolBarActive = true;

    // create toolbar
    memberToolBar = new QToolBar("Place Members");
    QWidget *jointWidg1 = new QWidget;
    QWidget *jointWidg2 = new QWidget;

    memberToolBar->isMovable();

    // add labels
    QLabel *Title = new QLabel("Insert Members");
    QLabel *FText = new QLabel("1st:");
    QLabel *SText = new QLabel("2nd:");

    // insert button
    addMember = new QPushButton("ADD");

    addXText = new QLineEdit;
    addYText = new QLineEdit;

    addXText->resize(25,addXText->height());

    // add layouts
    QHBoxLayout *xLay = new QHBoxLayout();
    xLay->addWidget(FText);
    xLay->addWidget(addXText);

    QHBoxLayout *yLay = new QHBoxLayout();
    yLay->addWidget(SText);
    yLay->addWidget(addYText);

    memberToolBar->addWidget(Title);
    memberToolBar->addSeparator();

    jointWidg1->setLayout(xLay);
    jointWidg2->setLayout(yLay);

    memberToolBar->addWidget(jointWidg1);
    memberToolBar->addWidget(jointWidg2);

    memberToolBar->addWidget(addMember);

    this->addToolBar(memberToolBar);

    connect(addMember,SIGNAL(clicked()),this,SLOT(on_pushButton_addmember_released()));


}

void MainWindow::clearToolbars()
{
    // get rid of all tool bars
    if(jToolBarActive == true)
    {
        this->removeToolBar(jointToolBar);
        jToolBarActive = false;
    }
    if(mToolBarActive == true)
    {
        this->removeToolBar(memberToolBar);
        mToolBarActive = false;
    }
    if(cToolBarActive == true)
    {
        this->removeToolBar(constraintToolBar);
        cToolBarActive = false;
    }
    if(fToolBarActive == true)
    {
        this->removeToolBar(forceToolBar);
        fToolBarActive = false;
    }

}

void MainWindow::on_pushButton_addmember_released()
{
     std::vector<int> mPoints;

    QString myOne = addXText->text();
    QString myTwo = addYText->text();

    int One = myOne.toInt();
    int Two = myTwo.toInt();

    mPoints.push_back(One);
    mPoints.push_back(Two);

    myStructure.conn.push_back(mPoints);

    QGraphicsLineItem *newMember = new QGraphicsLineItem;

    drawnMembers.push_back(newMember);

    drawJoint();
    drawMembers();
}

void MainWindow::on_actionConstraints_triggered()
{

    clearToolbars();

    cToolBarActive = true;

    // create toolbar
    constraintToolBar = new QToolBar("Place Constraint");
    QWidget *jointWidg = new QWidget;
    QWidget *xWidg = new QWidget;
    QWidget *yWidg = new QWidget;
    QWidget *rzWidg = new QWidget;

    constraintToolBar->isMovable();

    // add labels
    QLabel *Title = new QLabel("Insert Members");
    QLabel *JText = new QLabel("Joint:");
    QLabel *FText = new QLabel("X:");
    QLabel *SText = new QLabel("Y:");
    QLabel *TText = new QLabel("Rz:");

    constX = new QRadioButton;
    constY = new QRadioButton;
    constRz = new QRadioButton;

    // insert button
    addConstraint = new QPushButton("ADD");

    addXText = new QLineEdit;

    addXText->resize(25,addXText->height());

    // add layouts
    QHBoxLayout *jLay = new QHBoxLayout();
    jLay->addWidget(JText);
    jLay->addWidget(addXText);

    QHBoxLayout *fLay = new QHBoxLayout();
    fLay->addWidget(FText);
    fLay->addWidget(constX);

    QHBoxLayout *sLay = new QHBoxLayout();
    sLay->addWidget(SText);
    sLay->addWidget(constY);

    QHBoxLayout *tLay = new QHBoxLayout();
    tLay->addWidget(TText);
    tLay->addWidget(constRz);


    constraintToolBar->addWidget(Title);
    constraintToolBar->addSeparator();

    jointWidg->setLayout(jLay);
    xWidg->setLayout(fLay);
    yWidg->setLayout(sLay);
    rzWidg->setLayout(tLay);

    constraintToolBar->addWidget(jointWidg);
    constraintToolBar->addWidget(xWidg);
    constraintToolBar->addWidget(yWidg);
    constraintToolBar->addWidget(rzWidg);

    constraintToolBar->addWidget(addConstraint);

    this->addToolBar(constraintToolBar);

    connect(addConstraint,SIGNAL(clicked()),this,SLOT(on_pushButton_addconstraint_released()));
}

void MainWindow::on_pushButton_addconstraint_released()
{
    std::vector<int> constPoint;

    QString constJoint = addXText->text();

    int constJointNum = constJoint.toInt();

    if(constX->isChecked())
    {
        constPoint.push_back(constJointNum);
        constPoint.push_back(1);
        myStructure.constMat.push_back(constPoint);
        constPoint.clear();
    }
    if(constY->isChecked())
    {
        constPoint.push_back(constJointNum);
        constPoint.push_back(2);
        myStructure.constMat.push_back(constPoint);
        constPoint.clear();
    }
    if(constRz->isChecked())
    {
        constPoint.push_back(constJointNum);
        constPoint.push_back(3);
        myStructure.constMat.push_back(constPoint);
        constPoint.clear();
    }

    drawDConstraints();
    drawJoint();
    drawMembers();
}

void MainWindow::on_pushButton_addforce_released()
{
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
    }
    if(constY->isChecked())
    {
        forcePoint.push_back(forceJointNum);
        forcePoint.push_back(2);
        forcePoint.push_back(forceDoubleMag);
        myStructure.loadMat.push_back(forcePoint);
        forcePoint.clear();
    }
    if(constRz->isChecked())
    {
        forcePoint.push_back(forceJointNum);
        forcePoint.push_back(3);
        forcePoint.push_back(forceDoubleMag);
        myStructure.loadMat.push_back(forcePoint);
        forcePoint.clear();
    }

    drawDConstraints();
    drawJoint();
    drawMembers();
    drawDForces();
}

void MainWindow::drawDConstraints()
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

void MainWindow::drawDForces()
{
    QBrush momBrush(Qt::transparent);
    QBrush momBrush2(Qt::yellow);
    QBrush loadBrush(Qt::green);
    QPen loadPen(Qt::green);
    QPen momPen(Qt::yellow);
    loadPen.setWidth(1);
    momPen.setWidth(3);

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

        double x1 = myStructure.xstruct[m][0];
        double y1 = -myStructure.xstruct[m][1];

        myText = new QGraphicsTextItem(forceT);
        myText->setDefaultTextColor(Qt::white);

        if(dir==1)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1-50,y1,loadPen);

            // draw triangle
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-20,y1+5) << QPointF(x1-20,y1-5);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1-80);
            myText->setY(y1);

            scene->addItem(myText);

        }
        else if(dir==2)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1,y1-50,loadPen);

            // draw triangle
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1,y1) << QPointF(x1-5,y1-20) << QPointF(x1+5,y1-20);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,loadPen,loadBrush);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1+5);
            myText->setY(y1-50);

            scene->addItem(myText);

        }
        else
        {
            myStructCirc = scene->addEllipse(x1-20, y1-20, 40, 40, momPen, momBrush);

            // draw triangle
            noDrawnTransShape.clear();
            noDrawnTransShape << QPointF(x1+10,y1-20) << QPointF(x1-10,y1-10) << QPointF(x1-10,y1-30);
            noDrawnTrans = scene->addPolygon(noDrawnTransShape,momPen,momBrush2);

            font.setPixelSize(30);
            font.setBold(false);
            font.setFamily("Calibri");

            myText->setX(x1-25);
            myText->setY(y1-60);

            scene->addItem(myText);
        }
    }
}

void MainWindow::on_actionForces_triggered()
{
    clearToolbars();

    fToolBarActive = true;

    // create toolbar
    forceToolBar = new QToolBar("Place Force");
    QWidget *jointWidg = new QWidget;
    QWidget *xWidg = new QWidget;
    QWidget *yWidg = new QWidget;
    QWidget *momWidg = new QWidget;
    QWidget *magWidg = new QWidget;

    forceToolBar->isMovable();

    // add labels
    QLabel *Title = new QLabel("Place Forces");
    QLabel *JText = new QLabel("Joint:");
    QLabel *MText = new QLabel("Magnitude:");
    QLabel *FText = new QLabel("X:");
    QLabel *SText = new QLabel("Y:");
    QLabel *TText = new QLabel("Moment:");

    constX = new QRadioButton;
    constY = new QRadioButton;
    constRz = new QRadioButton;

    // insert button
    addForce = new QPushButton("ADD");

    addXText = new QLineEdit;
    addYText = new QLineEdit;

    addXText->resize(25,addXText->height());

    // add layouts
    QHBoxLayout *jLay = new QHBoxLayout();
    jLay->addWidget(JText);
    jLay->addWidget(addXText);

    QHBoxLayout *mLay = new QHBoxLayout();
    mLay->addWidget(MText);
    mLay->addWidget(addYText);

    QHBoxLayout *fLay = new QHBoxLayout();
    fLay->addWidget(FText);
    fLay->addWidget(constX);

    QHBoxLayout *sLay = new QHBoxLayout();
    sLay->addWidget(SText);
    sLay->addWidget(constY);

    QHBoxLayout *tLay = new QHBoxLayout();
    tLay->addWidget(TText);
    tLay->addWidget(constRz);

    forceToolBar->addWidget(Title);
    forceToolBar->addSeparator();

    jointWidg->setLayout(jLay);
    xWidg->setLayout(fLay);
    yWidg->setLayout(sLay);
    momWidg->setLayout(tLay);
    magWidg->setLayout(mLay);

    forceToolBar->addWidget(jointWidg);
    forceToolBar->addWidget(magWidg);
    forceToolBar->addWidget(xWidg);
    forceToolBar->addWidget(yWidg);
    forceToolBar->addWidget(momWidg);

    forceToolBar->addWidget(addForce);

    this->addToolBar(forceToolBar);

    connect(addForce,SIGNAL(clicked()),this,SLOT(on_pushButton_addforce_released()));
}

void MainWindow::on_actionProperties_triggered()
{

}
