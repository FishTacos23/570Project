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
