#include "primary_expression_parser.h"
#include "token.h"
#include "number.h"

#include <stack>
#include <cstring>

using std::stack;

#include <iostream>

short SortYardAlgorithm(string const& mainExpr, string& outMainExpr)
{
    outMainExpr.clear();
    outMainExpr.reserve(mainExpr.length());

    stack<char> stakOper;
    unsigned strLength = mainExpr.length();
    char token;
    bool checkValue = false, isFunc = false, leftP = false, isNumber = false;
    unsigned k = 0, totalNumb = 0;

    for (unsigned i = 0; i < strLength; ++i)
    {
        token = mainExpr[i];
        //std::cout << token << std::endl;

        if (isspace(token))
        {
            if (leftP && isNumber)
            {
                isNumber = false;
            }

            continue;
        }
        else if (IsDigit(token))
        {
            if (leftP && !isNumber)
            {
                isNumber = true;
                ++totalNumb;
            }

            outMainExpr.push_back(token);
        }
        else if (IsIdentifier(token))
        {
            outMainExpr.push_back(token);
            outMainExpr.push_back(' ');
        }
        else if (IsFunction(token))
        {
            int funcCode = 0;
            for (k = 0; mainExpr[i + k] != '('; ++k)
            {
                if (i + k < strLength)
                {
                    if (!IsFunction(mainExpr[i + k]))
                    {
                        return false;
                    }

                    funcCode += int(mainExpr[i + k]);
                }
                else { return -1; }

                if (!isFunc)
                    isFunc = true;
            }

            funcCode = GetFuncCode(funcCode);

            if (funcCode == -1)
            {
                return -2;
            }

            stakOper.push('}');
            stakOper.push(funcCode);
            stakOper.push('$');

            i += k - 1;
        }
        else if (token == ',')
        {
            checkValue = false;
            outMainExpr.push_back(' ');

            while (!stakOper.empty())
            {
                if (stakOper.top() == '(')
                {
                    checkValue = true;
                    break;
                }
                else
                {
                    outMainExpr.push_back(stakOper.top());
                    outMainExpr.push_back(' ');

                    stakOper.pop();
                }
            }

            if (!checkValue)
                return -3;
        }
        else if (IsOper(token))
        {
            if (leftP && isNumber)
            {
                isNumber = false;
            }

            outMainExpr.push_back(' ');

            while (!stakOper.empty() && IsOper(stakOper.top()) && (Priority(token) <= Priority(stakOper.top())))
            {
                outMainExpr.push_back(stakOper.top());
                outMainExpr.push_back(' ');
                stakOper.pop();
            }

            stakOper.push(token);
        }
        else if (token == '(')
        {
            if (!leftP)
            {
                leftP = true;
            }
            else
            {
                if (totalNumb)
                    totalNumb = 0;
            }

            stakOper.push(token);
        }
        else if (token == ')')
        {
            outMainExpr.push_back(' ');

            checkValue = false;
            unsigned operCount = 0;
            char prevOper = '\0';

            while (!stakOper.empty())
            {
                if (stakOper.top() == '(')
                {
                    if (operCount == 1 && totalNumb == 1)
                    {
                        char prevOper = outMainExpr[outMainExpr.length() - 2];

                        outMainExpr[outMainExpr.length() - 2] = '#';
                        outMainExpr.push_back(prevOper);
                        outMainExpr.push_back(' ');

                    }

                    checkValue = true;
                    break;
                }
                else
                {
                    outMainExpr.push_back(stakOper.top());
                    outMainExpr.push_back(' ');

                    stakOper.pop();
                    ++operCount;
                }
            }

            if (!checkValue)
                return -4;

            stakOper.pop();
            leftP = false;
            totalNumb = 0;

            if (isFunc)
            {
                if (stakOper.top() == '$')
                {
                    while (!stakOper.empty())
                    {
                        if (stakOper.top() == '}')
                        {
                            outMainExpr.push_back(stakOper.top());
                            outMainExpr.push_back(' ');

                            break;
                        }

                        outMainExpr.push_back(stakOper.top());
                        outMainExpr.push_back(' ');

                        stakOper.pop();
                    }

                    stakOper.pop();
                    isFunc = false;
                }
            }
        }
        else
        {
           //std::cout << -5 << ' ' << token << std::endl;
            return -5;
        }
    }

    outMainExpr.push_back(' ');

    while (!stakOper.empty())
    {
        if (stakOper.top() == '(' || stakOper.top() == ')')
        {
            return -6;
        }

        outMainExpr.push_back(stakOper.top());
        outMainExpr.push_back(' ');

        stakOper.pop();
    }

    return 0;
}

short ExecuteExpr(string const& outMainExpr, long double& outValue)
{
    stack<long double> stackNumber;

    long double left = 0, right = 0, result = 0;
    bool isFunc = false, isUnarMinus = false, isAssign = false;
   // char* currentAssignValue;

    for (char* token = strtok((char*)outMainExpr.c_str(), " "); token; token = strtok(NULL, " "))
    {
        if (isFunc)
        {
            switch (token[0])
            {
            case '0':
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(sin(left));
                break;
            case '1':
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(cos(left));
                break;
            case '2':
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(tan(left));
                break;
            case '3':
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(1 / pow(tan(left), 2));
                break;
            case '4':
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(log(left));
                break;
            case '5':
                right = stackNumber.top();  stackNumber.pop();
                left = stackNumber.top();  stackNumber.pop();
                stackNumber.push(log10(right) / log10(left));
                break;
            default: return -1;
            }
            isFunc = false;
        }
        else if (IsOper(token[0]))
        {
            if (isUnarMinus)
            {
                left = stackNumber.top();  stackNumber.pop();
                result = -1 * left;
                isUnarMinus = false;
            }
            else
            {
                
                if (stackNumber.size() < CountOfArgs(token[0]))
                {
                    return -2;
                }

                right = stackNumber.top();  stackNumber.pop();
                left = stackNumber.top();  stackNumber.pop();

                switch (token[0])
                {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/': result = left / right; break;
                //case '^': result = pow(left, right); break;
                //case '=': UpdateMemoryOfConst(currentAssignValue, result); break;
                }

                if (isnan(result))
                {
                    //cout << setw(10) << "error : " << left << ' ' << token[0] << ' ' << right << " = " << result << endl;
                    return -3;
                }
            }
            stackNumber.push(result);
        }
        else if (IsDigit(token[0]))
        {
            if (!StrToReal(token, result))
                return -4;
            stackNumber.push(result);
        }
        else if (IsIdentifier(token[0]))
        {
            /*
            if (!GetConstByCode(token, result))
            {
                currentAssignValue = token;
                isAssign = true;
            }
            else
            {
                stackNumber.push(result);
            }*/
        }
        else if (token[0] == '$')
        {
            isFunc = true;
        }
        else if (token[0] == '#')
        {
            isUnarMinus = true;
        }
    }

    outValue = stackNumber.top();

    return 0;
}