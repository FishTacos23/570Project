#ifndef ANALYZE_H
#define ANALYZE_H
#include <vector>
#include "tokenize.h"
#include <QGraphicsLineItem>

class Analyze
{
public:
    Analyze();

    void preprocessing();
    void AssembleStructStiff();
    void Triangularization();
    void AssembleStructForce();
    void BackSub();
    void postprocessing();

    void getDispl();
    void StructDOF();
    std::vector<std::vector<double>> StructToMemCoord();
    void MemToStructStiffs();
    std::vector<std::vector<double>> MatTriangSelf();
    std::vector<std::vector<double>> JointToStructLoad();
    void MemToStructForce();
    void MatVecMinus();
    void MatBackSelf();
    std::vector<std::vector<double>> StructToJointDisp();

    void clearStructVar();

    std::vector<std::vector<double>> xstruct;
    std::vector<std::vector<int>> conn;
    std::vector<std::vector<int>> constMat;
    std::vector<std::vector<double>> loadMat;
    std::vector<double> properties;
    std::string StructType;
    std::vector<std::vector<int>> SDOF;

private:

    std::vector<std::vector<double>> KStruct;
    std::vector<double> FStruct;
    std::vector<double> UStruct;

    std::vector<std::vector<double>> kmem;
    std::vector<double> fmem;
    std::vector<double> umem;

    int njoints;
    int ndofs;

};

#endif // ANALYZE_H
