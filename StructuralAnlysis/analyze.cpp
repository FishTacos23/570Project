#include "analyze.h"
#include "pframe.h"

Analyze::Analyze()
{

}

void Analyze::preprocessing()
{

    njoints = xstruct.size();
    ndofs = PFrame().ndofs;

    // structDOF's
    StructDOF();

    // loop through members

        // StructToMemCoord

        // PFrameLenRot

}

void Analyze::AssembleStructStiff()
{
    // loop through members

        // PFrameStiff

        // MemtoStructStiff
}

void Analyze::Triangularization()
{
    // MatTriangSelf
}

void Analyze::AssembleStructForce()
{
    // loop through joints and directions

        // JointToStructLoad

    // loop through members

        // PFrameDistr

        // PFrameForce

        // MemToStructForce
}

void Analyze::BackSub()
{
    // MatVecMinus

    // MatBackSelf
}

void Analyze::postprocessing()
{
    // loop through joints and disp

        // StructToJointDisp

}

void Analyze::getDispl()
{
    // return joint displacements

}

void Analyze::StructDOF()
{
    int num = 1;
    int s = constMat.size();
    int m;
    int n;

    // loop through making matrix of 1's of correct size

    // DOF matrix is # of joints x # of DOFS/Joint
    for(int i = 0; i < njoints; i++)
    {
        std::vector<int> row;

        for(int j = 0; j < ndofs; j++)
        {
            row.push_back(1);
        }
        SDOF.push_back(row);
    }

    // loop through const matrix, write zeros to DOF Mat
    for(int i = 0; i < s; i++)
    {
        m = constMat[i][0]-1;
        n = constMat[i][1]-1;

        SDOF[m][n] = 0;
    }

    // increment positive numbers
    for(int i = 0; i < njoints; i++)
    {
        for(int j = 0; j < ndofs; j++)
        {
            if(SDOF[i][j] > 0)
            {
                SDOF[i][j] = num;
                num++;
            }
        }
    }

}

std::vector<std::vector<double> > Analyze::StructToMemCoord()
{

}

void Analyze::MemToStructStiffs()
{

}

std::vector<std::vector<double> > Analyze::MatTriangSelf()
{

}

std::vector<std::vector<double> > Analyze::JointToStructLoad()
{

}

void Analyze::MemToStructForce()
{

}

void Analyze::MatVecMinus()
{

}

void Analyze::MatBackSelf()
{

}

std::vector<std::vector<double> > Analyze::StructToJointDisp()
{

}

void Analyze::clearStructVar()
{
    KStruct.clear();
    FStruct.clear();
    UStruct.clear();
}
