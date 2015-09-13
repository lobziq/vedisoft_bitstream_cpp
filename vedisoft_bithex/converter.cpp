#include "converter.h"


converter::converter()
{
	
}

std::string converter::binaryToHex(std::string byte)
{
	if (byte.length() != 4)
	{
		//std::cout << "incorrect byte value (length != 4)" << std::endl;
		return "INCORRECT DATA LENGTH (NOT EQUAL 4)";
	}

	std::map <std::string, std::string> m;

	m["0000"] = "0";
	m["0001"] = "1";
	m["0010"] = "2";
	m["0011"] = "3";
	m["0100"] = "4";
	m["0101"] = "5";
	m["0110"] = "6";
	m["0111"] = "7";
	m["1000"] = "8";
	m["1001"] = "9";
	m["1010"] = "A";
	m["1011"] = "B";
	m["1100"] = "C";
	m["1101"] = "D";
	m["1110"] = "E";
	m["1111"] = "F";

	if (m[byte] == "")
	{
		//std::cout << "Incorrect byte value" << std::endl;
		return "INCORRECT BYTE VALUE";
	}

	return m[byte];
}

std::string converter::hexToBinary(char hex)
{
	std::map <char, std::string> m;

	m['0'] = "0000";
	m['1'] = "0001";
	m['2'] = "0010";
	m['3'] = "0011";
	m['4'] = "0100";
	m['5'] = "0101";
	m['6'] = "0110";
	m['7'] = "0111";
	m['8'] = "1000";
	m['9'] = "1001";
	m['A'] = "1010";
	m['B'] = "1011";
	m['C'] = "1100";
	m['D'] = "1101";
	m['E'] = "1110";
	m['F'] = "1111";

	if (m[hex] == "")
	{
		//std::cout << "Incorrect byte value" << std::endl;
		return "INCORRECT HEX VALUE";
	}

	return m[hex];
}

std::string converter::decimalToHex(unsigned short dec)
{
	std::string output;
	char c[7] = "ABCDEF";
	unsigned short n;
	unsigned short oldn = dec;
	unsigned short remainder;

	for (int i = 0; i < 4; i++)
	{
		n = oldn / 16;
		remainder = oldn - (16 * n);
		oldn = n;
		if (remainder > 9)
		{
			output = c[remainder - 10] + output;
		}
		else
		{
			output = std::to_string(remainder) + output;
		}
	}

	//unsigned short n = dec / 16;
	//unsigned short remainder = dec - (16 * n);

	//std::cout << n << std::endl;

	return output;
}


converter::~converter()
{
}
