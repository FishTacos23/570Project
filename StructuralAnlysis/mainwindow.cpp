#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "tokenize.h"
#include <fstream>
#include "analyze.h"
#include <iostream>

static Analyze myStructure;

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
    // get file name
    QString fileNameQ = QFileDialog::getOpenFileName(this,"Open Shape File", "","*.txt");
    std::string fileName = fileNameQ.toStdString();

    readFile(fileName);

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
    for(int i = 0; i < myStructure.xstruct.size();i++)
    {
        std::cout << myStructure.xstruct[i][0] << " " << myStructure.xstruct[i][1] << std::endl;
    }
    std::cout << "The members are from joints: " << std::endl;
    for(int i = 0; i < myStructure.conn.size();i++)
    {
        std::cout << myStructure.conn[i][0] << " " << myStructure.conn[i][1] << std::endl;
    }
    std::cout << "The constraints are: " << std::endl;
    for(int i  = 0; i < myStructure.constMat.size(); i++)
    {
        std::cout << myStructure.constMat[i][0] << " " << myStructure.constMat[i][1] << std::endl;
    }
    std::cout << "The joint loads are: " << std::endl;
    for(int i = 0; i < myStructure.loadMat.size(); i++)
    {
        std::cout << myStructure.loadMat[i][0] << " " << myStructure.loadMat[i][1] << " " << myStructure.loadMat[i][2] << std::endl;
    }
    std::cout << "The member properties are: " << std::endl;
    for(int i = 0; i < myStructure.properties.size(); i++)
    {
        std::cout << myStructure.properties[i] << std::endl;
    }
}
