#include "pframe.h"
#include <math.h>

PFrame::PFrame()
{

}

std::vector<double> PFrame::PFrameLenRot(std::vector<std::vector<double> > Coord)
{
    // return vector of 2 numbers, length and rotation
    std::vector<double> lenRot;

    double length;
    double s1 = pow(Coord[1][0]-Coord[0][0],2);
    double s2 = pow(Coord[1][1]-Coord[0][1],2);

    length = sqrt(s1+s2);

    lenRot.push_back(length);

    double rotation;
    rotation = atan((Coord[1][1]-Coord[0][1])/(Coord[1][0]-Coord[0][0]));

    lenRot.push_back(rotation);

    return lenRot;
}

std::vector<std::vector<double> > PFrame::PFrameStiff(std::vector<double> lenRot, std::vector<double> properties)
{
    // return stiffness matrix
    double E = properties[0];
    double A = properties[1];
    double I = properties[2];
    double L = lenRot[0];
    double R = lenRot[1];

    double a = E*A/L;
    double b = 12*E*I/(pow(L,3));
    double c = 6*E*I/(pow(L,2));
    double d = 4*E*I/L;
    double e = 2*E*I/L;

    // khat matrix
    // make matrix
    std::vector<std::vector<double>> kh;

    for(int i = 0; i < 6; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < 6; j++)
        {
            row.push_back(0.0);
        }
        kh.push_back(row);
    }

    // fill matrix
    kh[0][0] = a;
    kh[0][3] = -a;
    kh[1][1] = b;
    kh[1][2] = c;
    kh[1][4] = -b;
    kh[1][5] = c;
    kh[2][1] = c;
    kh[2][2] = d;
    kh[2][4] = -c;
    kh[2][5] = e;
    kh[3][0] = -a;
    kh[3][3] = a;
    kh[4][1] = -b;
    kh[4][2] = -c;
    kh[4][4] = b;
    kh[4][5] = -c;
    kh[5][1] = c;
    kh[5][2] = e;
    kh[5][4] = -c;
    kh[5][5] = d;

    // transformation matrix
    // make matrix
    std::vector<std::vector<double>> T;

    for(int i = 0; i < 6; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < 6; j++)
        {
            row.push_back(0.0);
        }
        T.push_back(row);
    }

    T[0][0] = cos(R);
    T[0][1] = sin(R);
    T[1][0] = -sin(R);
    T[1][1] = cos(R);
    T[2][2] = 1;
    T[3][3] = T[0][0];
    T[3][4] = T[0][1];
    T[4][3] = T[1][0];
    T[4][4] = T[1][1];
    T[5][5] = 1;

    // create temporary k
    std::vector<std::vector<double>> ktemp;

    for(int i = 0; i < 6; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < 6; j++)
        {
            row.push_back(0.0);
        }
        ktemp.push_back(row);
    }

    // multiply T transpose and kh
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            double sum = 0;
            for(int h = 0; h < 6; h++)
            {
                sum += T[h][j]*kh[h][i];
            }
            ktemp[i][j] = sum;
        }
    }

    // create k
    std::vector<std::vector<double>> k;

    for(int i = 0; i < 6; i++)
    {
        std::vector<double> row;
        for(int j = 0; j < 6; j++)
        {
            row.push_back(0.0);
        }
        k.push_back(row);
    }

    // multiply k and T
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            double sum=0;
            for(int h = 0; h < 6; h++)
            {
                double TT = T[h][j];
                double KK = ktemp[h][i];

                sum += ktemp[h][i]*T[h][j];
            }
            k[i][j] = sum;
        }
    }

    return k;
}

std::vector<std::vector<double> > PFrame::PFrameDistrib()
{

}

std::vector<std::vector<double> > PFrame::PFrameForce()
{

}
