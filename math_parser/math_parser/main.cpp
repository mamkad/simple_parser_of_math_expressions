#include <iostream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

#include "primary_expression_parser.h"

int main(int argc, char **argv)
{
    string mainExpr, resExpr;
    long double outValue;

    //string mainExpr = "COS(2*x+5*2+5/(34+4*(4-2^(9.4520023^(8/(5*2+9/21)-2*2)))) + SIN(5.23))"; //не поддерживает
    //string mainExpr = "COS(2*0.342104+5*2+5/(34+4*(4-2^(9.4520023^(8/(5*2+9/21)-2*2)))) + SIN(5.23))";
    //string mainExpr = "432d + 34";
    //string mainExpr = "LOG(2.2352, 8) + 1 / (12)";
    //string mainExpr = "(2.2352+ 8) + 1 / (12)";
    //string mainExpr = "SIN(45+23*(2-5+3-5)) ^ SIN(2+3*9/(9/3-1)) + COS(3+3*2/9+3)";
    //string mainExpr = "SIN(45+23*(2-5+3-5)) ^ 0.2";
    //string mainExpr = "(-67) + 45 + 22 + 15 + (-15)";

    switch (argc)
    {
    case 1:
        getline(cin, mainExpr, '\n'); break;

    case 2:
        mainExpr = std::istringstream(argv[1]).str(); break;

    default: return 1;
    }

    short retCode;

    if (!(retCode = SortYardAlgorithm(mainExpr, resExpr)))
        if (!(retCode = ExecuteExpr(resExpr, outValue)))
            cout << "result : " << outValue << endl;

	return retCode;
}









