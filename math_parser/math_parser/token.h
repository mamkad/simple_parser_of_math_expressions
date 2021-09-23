#pragma once

#include <cctype>

inline bool IsIdentifier(char const token)
{
    return (islower(token));
}

inline bool IsFunction(char const token)
{
    return (isupper(token));
}

inline bool IsOper(char const token)
{
    return (token == '+' || token == '-' || token == '/' || token == '*' /*|| token == '^' */ || token == '=');
}

inline bool IsDigit(char const token)
{
    return (isdigit(token) || token == '.');
}

inline short Priority(char const token)
{
    switch (token)
    {
    //case '^':           return 4;
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    case '=':           return 1;
    default: return -1;
    }
    return 0;
}

inline unsigned CountOfArgs(char const token)
{
    switch (token)
    {
    /*case '^': */case '*': case '/': case '+': case '-': return 2;
    case '=':           return 1;
    }
    return 0;
}

short GetFuncCode(unsigned numberArg)
{
    switch (numberArg)
    {
    case 234: return '0';
    case 229: return '1';
    case 227: return '2';
    case 294: return '3';
    case 154: return '4';
    case 226: return '5';
    case 166: return '6';
    }
    return -1;
}