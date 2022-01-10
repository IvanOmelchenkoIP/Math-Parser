#pragma once

class ExpressionParser
{
private:
	CharTypes cType;

	std::string input;

	std::map<int, std::string> exprNumbers;
	std::map<int, std::string> exprOperators;
	std::map<int, int> exprPriorities;
	std::map<int, std::string> exprBrackets;

	std::map<int, double> numsOrganized;
	
	double result;

	bool Parse();
	void OrganizeNumbers();

	void Calculate();
	bool IterateBrackets();
	double CountInInterval(int, int);

public:
	double Evaluate(std::string);
};

