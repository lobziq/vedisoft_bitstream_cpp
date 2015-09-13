#pragma once

#include <iostream>
#include <map>
#include <string>

class converter
{
public:
	converter();

	static std::string binaryToHex(std::string byte);
	static std::string decimalToHex(unsigned short dec);
	static std::string hexToBinary(char hex);


	~converter();

private:
};

