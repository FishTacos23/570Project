#ifndef ANALYZE_H
#define ANALYZE_H
#include <vector>

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
    std::vector<std::vector<double>> StructDOF();
    std::vector<std::vector<double>> StructToMemCoord();
    void MemToStructStiffs();
    std::vector<std::vector<double>> MatTriangSelf();
    std::vector<std::vector<double>> JointToStructLoad();
    void MemToStructForce();
    void MatVecMinus();
    void MatBackSelf();
    std::vector<std::vector<double>> StructToJointDisp();

private:


};

#endif // ANALYZE_H
