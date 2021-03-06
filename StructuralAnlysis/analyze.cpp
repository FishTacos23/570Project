#include "analyze.h"
#include "pframe.h"

Analyze::Analyze()
{

}

void Analyze::preprocessing()
{

    njoints = xstruct.size();
    ndofs = PFrame().ndofs;
    nmems = conn.size();

    // structDOF's
    StructDOF();

    // loop through members
    std::vector<double> oneLenRot;

    for(int i = 0; i < nmems; i++)
    {
        // StructToMemCoord
        std::vector<std::vector<double>> memberCoordinates = StructToMemCoord(i);

        // PFrameLenRot
        oneLenRot = PFrame::PFrameLenRot(memberCoordinates);

        lenRot.push_back(oneLenRot);
    }
}

void Analyze::AssembleStructStiff()
{

    // initialize Struct Stiff Mat
    for(int i = 0; i < nSDOF-1; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < nSDOF-1; j++)
        {
            row.push_back(0);
        }
        KStruct.push_back(row);
    }


    for(int i = 0; i < ndofs*2; i++)
    {
        compMtoS.push_back(0);
    }

    // loop through members
    for(int i = 0; i < nmems; i++)
    {
        // PFrameStiff
        kmem = PFrame::PFrameStiff(lenRot[i],properties);

        // MemtoStructStiff
        for(int j = 0; j < ndofs*2; j++)
        {
            compMtoS[j]=0;
        }

        // loop
        for(int j = 0; j < 2; j++)
        {
            int joint = conn[i][j];

            for(int k = 0; k < ndofs; k++)
            {
                if(SDOF[joint-1][k] != 0)
                {
                    if(j==0)
                    {
                        compMtoS[k] = SDOF[joint-1][k];
                    }
                    else
                    {
                        compMtoS[k+3] = SDOF[joint-1][k];
                    }
                }
            }
        }

        // loop through compMtoS
        for(int j=0; j<ndofs*2; j++)
        {
            if(compMtoS[j] != 0)
            {
                int m = compMtoS[j]-1;
                for(int k = 0; k<ndofs*2; k++)
                {
                    if(compMtoS[k] != 0)
                    {
                        int n = compMtoS[k]-1;
                        KStruct[m][n] += kmem[j][k];
                    }
                }
            }
        }
    }
}

void Analyze::Triangularization()
{
    // MatTriangSelf
    int s = KStruct.size();

    // loop through rows
    for(int i = 1; i < s; i++)
    {
        // loop through columns until diagonal
        for(int j = 0; j < i; j++)
        {
            double c = KStruct[i][j];
            KStruct[i][j] = c/KStruct[j][j];
            KStruct[j][i] = KStruct[i][j];

            // loop through column decrementing
            for(int k = j+1; k <= i; k++)
            {
                KStruct[i][k] -= c*KStruct[k][j];
                KStruct[k][i] = KStruct[i][k];
            }
        }
    }
}

void Analyze::AssembleStructForce()
{
    for(int i = 0; i < nSDOF-1; i++)
    {
        FStruct.push_back(0);
    }

    // loop through joints and directions
    int j;
    int dir;

    for(int i = 0; i < loadMat.size(); i++)
    {
        // JointToStructLoad
        j = loadMat[i][0];
        dir = loadMat[i][1];

        int m = SDOF[j-1][dir-1]-1;

        FStruct[m] = loadMat[i][2];
    }

//    // loop through members - this part will only be needed with distributed loads
//    for(int i = 0; i < nmems; i++)
//    {
//        // PFrameDistr

//        // PFrameForce

//        // MemToStructForce

//    }
}

void Analyze::BackSub()
{
    // MatVecMinus - only needed with suppport displacements

    // MatBackSelf
    MatBackSelf();

}

void Analyze::postprocessing()
{
    int s = SDOF.size();

    for(int i = 0; i < s; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < ndofs; j++)
        {
            row.push_back(0);
        }
        dxstruct.push_back(row);
    }

    // loop through joints and disp
        // loop through SDOF
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < ndofs; j++)
        {
            if(SDOF[i][j] != 0)
            {
                int m = SDOF[i][j]-1;
                dxstruct[i][j] = UStruct[m];
            }
        }
    }
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
    nSDOF = num;
}

std::vector<std::vector<double> > Analyze::StructToMemCoord(int memNum)
{
    // loop through conn matrix
    std::vector<std::vector<double>> memCoord;

    std::vector<double> jCoord;

    int j1 = conn[memNum][0];
    int j2 = conn[memNum][1];

    double x = xstruct[j1-1][0];
    double y = xstruct[j1-1][1];

    jCoord.push_back(x);
    jCoord.push_back(y);

    memCoord.push_back(jCoord);

    jCoord[0] = xstruct[j2-1][0];
    jCoord[1] = xstruct[j2-1][1];

    memCoord.push_back(jCoord);

    return memCoord;
}

void Analyze::MemToStructStiffs()
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
    // only needed for support displacement
}

void Analyze::MatBackSelf()
{

    std::vector<double> e;
    std::vector<double> d;
    for(int i = 0; i < nSDOF-1; i++)
    {
        e.push_back(0);
        d.push_back(0);
        UStruct.push_back(0);
    }

    // Le = b
    for(int i = 0; i < nSDOF-1; i++)
    {
        e[i] = FStruct[i];
        for(int j = i-1; j >= 0; j--)
        {
            e[i] -= e[j]*KStruct[i][j];
        }
    }

    // Dd = e
    for(int i = 0; i < nSDOF-1; i++)
    {
        d[i] = e[i]/KStruct[i][i];
    }

    // Lt c = d
    for(int i = 0; i < nSDOF-1; i++)
    {
        int num = nSDOF-i-2;
        UStruct[num] = d[num];
        for(int j = i; j > 0; j--)
        {
            UStruct[num] -= UStruct[j+num]*KStruct[j+num][num];
        }
    }
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
