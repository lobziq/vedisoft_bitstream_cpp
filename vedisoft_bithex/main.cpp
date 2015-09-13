#include <iostream>
#include <string>
#include <map>

#include <climits>

#include "converter.h"
#include "bitObject.h"
#include "parser.h"

int main()
{
	//bitObject b = bitObject(3, "0111111000111110111101111110");

	std::string s;

	parser p;

	while (1)
	{
		std::getline(std::cin, s);

		s = "FF5FA5FCFC80DD57E5F8FDFF";

		p.parseString(s, 600);

		std::cout << "Parsed value: " << p.getParsed() << std::endl;
	}

	//parser p = parser("FFFFFAAAFFFFFFFF", 600);
	//std::cout << p.getParsed() << std::endl;


	//std::cout << b.getValue() << std::endl;

	return 0;
}