#ifndef PFRAME_H
#define PFRAME_H
#include <vector>

class PFrame
{
public:
    PFrame();

    static std::vector<double> PFrameLenRot();
    static std::vector<std::vector<double>> PFrameStiff();
    static std::vector<std::vector<double>> PFrameDistrib();
    static std::vector<std::vector<double>> PFrameForce();

    int ndofs = 3;

};

#endif // PFRAME_H
