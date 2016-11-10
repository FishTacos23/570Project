#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "tokenize.h"
#include <fstream>
#include "analyze.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>

static Analyze myStructure;
QPainter myDrawing;
QPointF myCenter;
QPainterPath text;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    solved = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

    // read setup file  // THIS SECTION IS BREAKING DEBUGG!
    // get file name
    QString fileNameQ = QFileDialog::getOpenFileName(this,"Open Shape File", "","*.txt");
    std::string fileName = fileNameQ.toStdString();

//    std::string fileName = "C:\\Users\\Spencer\\Documents\\570project\\build-StructuralAnlysis-Desktop_Qt_5_7_0_MinGW_32bit-Debug\\StructureInput.txt";

    readFile(fileName);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    zoom = 3;

    // draw structure
    drawStructure();
    drawConstraints();
    drawForces();

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

    // make sure you are reading the file
    std::cout << "The structure is a: " << myStructure.StructType << std::endl;
    std::cout << "The joint coordinates are: " << std::endl;
    for(uint i = 0; i < myStructure.xstruct.size();i++)
    {
        std::cout << myStructure.xstruct[i][0] << " " << myStructure.xstruct[i][1] << std::endl;
    }
    std::cout << "The members are from joints: " << std::endl;
    for(uint i = 0; i < myStructure.conn.size();i++)
    {
        std::cout << myStructure.conn[i][0] << " " << myStructure.conn[i][1] << std::endl;
    }
    std::cout << "The constraints are: " << std::endl;
    for(uint i  = 0; i < myStructure.constMat.size(); i++)
    {
        std::cout << myStructure.constMat[i][0] << " " << myStructure.constMat[i][1] << std::endl;
    }
    std::cout << "The joint loads are: " << std::endl;
    for(uint i = 0; i < myStructure.loadMat.size(); i++)
    {
        std::cout << myStructure.loadMat[i][0] << " " << myStructure.loadMat[i][1] << " " << myStructure.loadMat[i][2] << std::endl;
    }
    std::cout << "The member properties are: " << std::endl;
    for(uint i = 0; i < myStructure.properties.size(); i++)
    {
        std::cout << myStructure.properties[i] << std::endl;
    }
}

void MainWindow::drawStructure()
{
    //QPainter myDrawing;

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
    drawConstraints();
    drawForces();

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

void MainWindow::on_pushButton_ZoomIn_clicked()
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
            drawDStructure();
            drawConstraints();
            drawForces();
        }
        else
        {
            drawStructure();
            drawConstraints();
            drawForces();
        }
        myCenter.setX((xmax-xmin)/2);
        myCenter.setY(-(ymax-ymin)/2);
        ui->graphicsView->centerOn(myCenter);
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
            drawDStructure();
            drawConstraints();
            drawForces();
        }
        else
        {
            drawStructure();
            drawConstraints();
            drawForces();
        }

        myCenter.setX((xmax-xmin)/2);
        myCenter.setY(-(ymax-ymin)/2);
        ui->graphicsView->centerOn(myCenter);
    }
}

void MainWindow::on_pushButton_ZOut_clicked()
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
            drawDStructure();
            drawConstraints();
            drawForces();
        }
        else
        {
            drawStructure();
            drawConstraints();
            drawForces();
        }

        myCenter.setX((xmax-xmin)/2);
        myCenter.setY(-(ymax-ymin)/2);
        ui->graphicsView->centerOn(myCenter);
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
                drawDStructure();
                drawConstraints();
                drawForces();
            }
            else
            {
                drawStructure();
                drawConstraints();
                drawForces();
            }

            myCenter.setX((xmax-xmin)/2);
            myCenter.setY(-(ymax-ymin)/2);
            ui->graphicsView->centerOn(myCenter);
        }
    }
}

void MainWindow::on_actionClear_triggered()
{
    // clear the screan
    scene->clear();

    // clear variables
    myStructure.xstruct.clear();
    myStructure.conn.clear();
    myStructure.constMat.clear();
    myStructure.loadMat.clear();
    myStructure.properties.clear();
    myStructure.SDOF.clear();
    myStructure.clearStructVar();

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

        drawStructure();
        drawDStructure();

        solved = true;
    }
}

void MainWindow::on_horizontalSlider_scaleDisp_sliderMoved(int position)
{
    if(solved==true)
    {
        dDeform = 1;
        dDeform*=position;

        drawStructure();
        drawDStructure();
    }
}

void MainWindow::drawConstraints()
{
    QBrush constBrush(Qt::blue);
    QPen constPen(Qt::black);
    constPen.setWidth(2);

    // loop through constraint matrix
    for(int i = 0; i < myStructure.constMat.size(); i++)
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
    loadPen.setWidth(5);
    momPen.setWidth(3);

    // loop through constraint matrix
    for(uint i = 0; i < myStructure.loadMat.size(); i++)
    {
        int m = (int)myStructure.loadMat[i][0]-1;
        int dir = (int)myStructure.loadMat[i][1];
        std::string forceMag = std::to_string(myStructure.loadMat[i][2]);

        double x1 = myStructure.xstruct[m][0]*zoom;
        double y1 = -myStructure.xstruct[m][1]*zoom;

        if(dir==1)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1-30*zoom,y1,loadPen);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-10*zoom,y1+5*zoom) << QPointF(x1-10*zoom,y1-5*zoom);
            noTrans = scene->addPolygon(noTransShape,loadPen,loadBrush);

            QFont font;
            font.setPixelSize(5);
            font.setBold(false);
            font.setFamily("Calibri");

            text.addText();

        }
        else if(dir==2)
        {
            // draw main line
            myStrucLine = scene->addLine(x1,y1,x1,y1-30*zoom,loadPen);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1,y1) << QPointF(x1-5*zoom,y1-10*zoom) << QPointF(x1+5*zoom,y1-10*zoom);
            noTrans = scene->addPolygon(noTransShape,loadPen,loadBrush);
        }
        else
        {
            myStructCirc = scene->addEllipse(x1-10*zoom, y1-10*zoom, 20*zoom, 20*zoom,momPen,momBrush);

            // draw triangle
            noTransShape.clear();
            noTransShape << QPointF(x1+2,y1-10*zoom) << QPointF(x1-3*zoom,y1-6*zoom) << QPointF(x1-3*zoom,y1-14*zoom);
            noTrans = scene->addPolygon(noTransShape,momPen,momBrush2);
        }
    }
}
