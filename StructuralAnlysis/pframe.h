// /////////////////////////////////////////////////////////////////////////////////////////////////////
// Title:           Spencer's PFrame Analysis
// Description:     Solve Structure PFrame Variables
//                  Code is based off learning and methods from Dr. Balling's class
// Author:          Spencer Bunnell
// Date:            October 2016
// /////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PFRAME_H
#define PFRAME_H
#include <vector>

class PFrame
{
public:
    PFrame();

    static std::vector<double> PFrameLenRot(std::vector<std::vector<double>> Coord);
    static std::vector<std::vector<double>> PFrameStiff(std::vector<double> lenRot,std::vector<double> properties);
    static std::vector<std::vector<double>> PFrameDistrib();
    static std::vector<std::vector<double>> PFrameForce();
    static std::vector<std::vector<double>> PFrameReac(std::vector<std::vector<double>> lenRot,
                                                       std::vector<std::vector<std::vector<double>>> kmem,
                                                       std::vector<std::vector<double> > umem,
                                                       std::vector<std::vector<double> > fmem, int nmems);

    int ndofs = 3;

};

#endif // PFRAME_H
