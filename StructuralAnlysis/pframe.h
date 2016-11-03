#ifndef PFRAME_H
#define PFRAME_H
#include <vector>

class PFrame
{
public:
    PFrame();

    std::vector<double> PFrameLenRot();
    std::vector<std::vector<double>> PFrameStiff();
    std::vector<std::vector<double>> PFrameDistrib();
    std::vector<std::vector<double>> PFrameForce();
};

#endif // PFRAME_H
