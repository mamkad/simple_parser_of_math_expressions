#include "number.h"

#include <cmath>
#include <cctype>
#include <cstring>

static bool GetNumber(char const* strNumber, unsigned strLength, long double& outNumber)
{
    unsigned deg;

    for (deg = 0; strLength >= 1; --strLength)
    {
        if (isdigit(strNumber[strLength]))
        {
            outNumber += (strNumber[strLength] - '0') * pow(10, deg);
        }
        else if (strNumber[strLength] == '.')
        {
            continue;
        }
        else
        {
            return false;
        }
        ++deg;
    }

    outNumber += (strNumber[0] - '0') * pow(10, deg);

    return true;
}

bool StrToReal(char const* strNumber, long double& outNumber)
{
    char* pntIdx = (char*)strchr(strNumber, '.');
    unsigned strLength = strlen(strNumber) - 1;
    outNumber = 0.0;

    if (pntIdx)
    {
        if (!GetNumber(strNumber, strLength, outNumber))
            return false;

        unsigned deg = (strNumber + strLength) - pntIdx;
        outNumber /= pow(10, deg);
    }
    else
    {
        if (!GetNumber(strNumber, strLength, outNumber))
            return false;
    }

    return true;
}