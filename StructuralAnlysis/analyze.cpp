#include "analyze.h"

Analyze::Analyze()
{

    // preprocessing

    // Assemble Struct Stiff Mat

    // Triangularize

    // Assemble Struct Force Vec

    // Back Substitution

    // post processing

}

void Analyze::preprocessing()
{
    // read input file


    // get joints and coordinates mat

    // get member joint mat

    // get mat props

    // structDOF's

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

std::vector<std::vector<double> > Analyze::StructDOF()
{

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
