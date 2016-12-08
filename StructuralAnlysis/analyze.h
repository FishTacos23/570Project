// /////////////////////////////////////////////////////////////////////////////////////////////////////
// Title:           Spencer's Structure Stiffness Matrix Method
// Description:     Solve Structure Stiffness Matrix
//                  Code is based off learning and methods from Dr. Balling's class
// Author:          Spencer Bunnell
// Date:            October 2016
// /////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ANALYZE_H
#define ANALYZE_H
#include <vector>
#include "tokenize.h"
#include <QGraphicsLineItem>

class Analyze
{
public:
    Analyze();

    // main parts of the program
    void preprocessing();
    void AssembleStructStiff();
    void Triangularization();
    void AssembleStructForce();
    void BackSub();
    void postprocessing();

    // subfunctions
    void StructDOF();
    void MatVecMinus();
    void MatBackSelf();
    void CalcReacs();
    void clearStructVar();
    std::vector<std::vector<double>> StructToMemCoord(int memNum);

    bool checkReady();

    // variables
    std::vector<std::vector<double>> xstruct;
    std::vector<std::vector<double>> dxstruct;
    std::vector<std::vector<int>> conn;
    std::vector<std::vector<int>> constMat;
    std::vector<std::vector<double>> loadMat;
    std::vector<double> properties;
    std::string StructType;
    std::vector<std::vector<int>> SDOF;
    std::vector<std::vector<double>> lenRot;
    std::vector<std::vector<int>> compMtoS;
    std::vector<std::vector<double>> rmem;

private:

    // variables
    std::vector<std::vector<double>> KStruct;
    std::vector<double> FStruct;
    std::vector<double> UStruct;

    std::vector<std::vector<std::vector<double>>> kmem;
    std::vector<std::vector<double>> fmem;
    std::vector<std::vector<double>> umem;

    int njoints;
    int ndofs;
    int nmems;
    int nSDOF;

};

#endif // ANALYZE_H
