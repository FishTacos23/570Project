// /////////////////////////////////////////////////////////////////////////////////////////////////////
// Title:           Spencer's Tokenized Application
// Description:     Parse Text
//                  Based off of code presented by Professor McBride
// Author:          Spencer Bunnell
// Date:            October 2016
// /////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOKENIZE_H
#define TOKENIZE_H
#include <iostream>
#include <vector>

class tokenize
{
public:
    tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");
};

#endif // TOKENIZE_H
