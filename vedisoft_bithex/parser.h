#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "bitObject.h"
#include "converter.h"

class parser
{
public:
	parser();

	bool prepareString(std::string input, unsigned int maxLength);
	void parseString(std::string input, unsigned int maxLength);
	void invertString(std::string* s);

	std::string getParsed();

	~parser();

private:
	std::string leftOver;
	std::string inputString;
	std::string binaryString;
	std::vector <bitObject> objects;
};

