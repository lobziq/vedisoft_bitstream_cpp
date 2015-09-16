#include <iostream>
#include <string>
#include <map>

#include <climits>

#include "converter.h"
#include "bitObject.h"
#include "parser.h"

int main()
{
	const int maxLength = 600; //300 bytes is 600 hex symbols as one stands for 0.5 byte
	std::string s;
	parser p;

	p.parseString("7EA1", maxLength);

	std::string f;
	for (int i = 0; i < 8000; i++)
	{
		f += "1";
	}
	bitObject b = bitObject(4, f);
	std::cout << b.getValue() << std::endl;

	while (std::getline(std::cin, s))
	{
		

		
		
		s = "A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1A1";
		std::cout << s << std::endl;
		p.parseString(s, maxLength);

		std::cout << p.getParsed() << std::endl;
	}

	p.transferIsOver();
	p.parseString("", maxLength);
	std::cout << p.getParsed() << std::endl;

	//p.parseString()

	return 0;
}