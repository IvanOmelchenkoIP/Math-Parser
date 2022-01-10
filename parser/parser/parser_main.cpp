#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <math.h>

#include "parser_types.h"
#include "parser_main.h"

//ExpressionParser
double ExpressionParser::Evaluate(std::string expr)
{
	input = "(" + expr  + ")";

	Parse();
	OrganizeNumbers();

	Calculate();

	return result;
}

bool ExpressionParser::Parse()
{
	std::string tmp;
	for (int i = 0; i < input.size(); i++)
	{
		std::string character = input.substr(i, 1);

		if (character == " ")
		{
			continue;
		}
		else if (cType.IsNumber(character))
		{
			exprNumbers[i] = character;
		}
		else if (cType.IsOperator(character))
		{
			exprOperators[i] = character;
			exprPriorities[i] = cType.ReturnPriority(character);
		}
		else if (cType.IsBrackets(character))
		{
			exprBrackets[i] = character;
		}
	}
	return true;
}

void ExpressionParser::OrganizeNumbers()
{
	std::string tmp;
	int prev = -1;
	bool firstIteration = true;

	int i = 0;
	int size = exprNumbers.size();
	std::vector<int> keys(size);
	std::vector<std::string> values(size);

	for (auto iter = exprNumbers.begin(); iter != exprNumbers.end(); iter++)
	{
		int key = iter->first;
		std::string value = iter->second;

		keys[i] = key;
		values[i] = value;
		i++;
	}

	for (int i = 0; i < size; i++)
	{
		int key = keys[i];
		std::string value = values[i];

		if (key - prev > 1 && prev != -1)
		{
			numsOrganized[prev] = (double)atof(tmp.c_str());
			tmp.erase();
		}

		tmp += values[i];
		prev = keys[i];

		if (i == size - 1)
		{
			numsOrganized[key] = (double)atof(tmp.c_str());
		}
	}
}


void ExpressionParser::Calculate()
{
	double res;
	
	while (true)
	{
		if (IterateBrackets()) break;
	}
	
}

bool ExpressionParser::IterateBrackets()
{
	if (!exprBrackets.size()) return true;;

	int left, right;
	for (auto iter = exprBrackets.begin(); iter != exprBrackets.end(); iter++)
	{
		int index = iter->first;
		std::string bracket = iter->second;

		if (bracket == "(")
		{
			left = index;
		}
		else if (bracket == ")")
		{
			right = index;
			result = CountInInterval(left, right);
			break;
		}
	}
	exprBrackets.erase(left);
	exprBrackets.erase(right);
	return false;
}


double ExpressionParser::CountInInterval(int left, int right)
{
	int assignInd;

	//creating temporary structure for operators
	std::map<int, std::string> tmpOpers;
	std::map<int, int> tmpPriors;

	for (auto iter = exprOperators.begin(); iter != exprOperators.end(); iter++)
	{
		int index = iter->first;
		std::string oper = iter->second;

		if (left > index) continue;
		if (index > right) break;

		tmpOpers[index] = oper;
		tmpPriors[index] = exprPriorities[index];
	}

	for (auto iter = tmpOpers.begin(); iter != tmpOpers.end(); iter++)
	{
		int index = iter->first;

		exprOperators.erase(index);
		exprPriorities.erase(index);
	}

	//creating temporary structure for numbers
	std::map<int, double> tmpNums;

	for (auto iter = numsOrganized.begin(); iter != numsOrganized.end(); iter++)
	{
		int index = iter->first;
		double num = iter->second;

		if (left > index) continue;
		if (index > right) break;

		tmpNums[index] = num;
		assignInd = index;
	}

	for (auto iter = tmpNums.begin(); iter != tmpNums.end(); iter++)
	{
		int index = iter->first;

		numsOrganized.erase(index);
	}

	//counting loop
	double innerResult;
	while (true)
	{
		//break condition
		if (tmpNums.size() <= 1 && !tmpOpers.size()) break;

		//getting numbers and operators for counting
		int maxPrior = 0;
		int maxPriorInd;
		for (auto iter = tmpPriors.begin(); iter != tmpPriors.end(); iter++)
		{
			int index = iter->first;
			int prior = iter->second;

			if (prior > maxPrior) maxPriorInd = index;
		}

		int prevInd = -1, curInd;
		double prevNum = NULL, curNum;
		for (auto iter = tmpNums.begin(); iter != tmpNums.end(); iter++)
		{
			int index = iter->first;
			double num = iter->second;

			if (index > maxPriorInd)
			{
				curInd = index;
				curNum = num;

				if (prevInd > -1) prevNum = tmpNums[prevInd];
				break;
			}

			prevInd = index;
		}

		//erasing used numbers and operators
		std::string chosenOper = tmpOpers[maxPriorInd];

		tmpPriors.erase(maxPriorInd);
		tmpOpers.erase(maxPriorInd);

		tmpNums.erase(curInd);
		if (prevInd) tmpNums.erase(prevInd);

		//counting
		double res;
		if (chosenOper == "+")
		{
			res = prevNum + curNum;
		}
		else if (chosenOper == "-")
		{
			if (prevNum == NULL) res = 0 - curNum;
			res = prevNum - curNum;
		}
		else if (chosenOper == "*")
		{
			res = prevNum * curNum;
		}
		else if (chosenOper == "/")
		{
			res = prevNum / curNum;
		}
		else if (chosenOper == "^")
		{
			res = pow(prevNum, curNum);
		}

		innerResult = tmpNums[curInd] = res;
	}

	numsOrganized[assignInd] = innerResult;

	return innerResult;
}