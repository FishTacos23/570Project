// /////////////////////////////////////////////////////////////////////////////////////////////////////
// Title:           Spencer's Tokenized Application
// Description:     Parse Text
//                  Based off of code presented by Professor McBride
// Author:          Spencer Bunnell
// Date:            October 2016
// /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tokenize.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

tokenize::tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
    // skip any delimiters that may be at the beginning
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // find the first text to be tokenized
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while(std::string::npos != pos || std::string::npos != lastPos)
    {
        // take everything between 2 delimiters and push it to tokens
        tokens.push_back(str.substr(lastPos,pos-lastPos));

        // reset pos and lastpos
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}
