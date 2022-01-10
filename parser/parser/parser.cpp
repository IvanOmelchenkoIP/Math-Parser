#include <iostream>

#include <string>
#include <map>
#include <vector>>
#include <math.h>

#include "parser_types.h"
#include "parser_main.h"

int main()
{
    //tests
    ExpressionParser ep;

    std::string expr1 = "6^2";
    std::cout << ep.Evaluate(expr1) << '\n';

    std::string expr2 = "32 - 8* 12/(62 * 4)";
    std::cout << ep.Evaluate(expr2);

    char exit;
    std::cin >> exit;
}
