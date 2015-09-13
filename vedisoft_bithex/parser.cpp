#include "parser.h"

parser::parser()
{
	//
}

void parser::invertString(std::string* s)
{
	std::string temp;
	for (int i = s->length() - 1; i >= 0; i--)
	{
		temp += s->at(i);
	}
	*s = temp;
}

bool parser::prepareString(std::string input, unsigned int maxLength)
{
	this->inputString = input;
	binaryString.clear();

	//checking for all string conditions, converting hex to binary + swapping byte contents
	if (inputString.length() > maxLength)
	{
		std::cerr << "Incorrect input string size (more than 300 bytes)" << std::endl;
		return false;
	}
	if (inputString.length() == 0)
	{
		std::cerr << "Input string is empty" << std::endl;
		return false;
	} 
	for (int i = 0; i < inputString.length(); i+=2)
	{
		std::string s;
		s += converter::hexToBinary(inputString.at(i));
		s += converter::hexToBinary(inputString.at(i + 1));
		if (s == "INCORRECT HEX VALUE")
		{
			std::cerr << "Incorrect symbols in string" << std::endl;
			return false;
		}
		else
		{
			invertString(&s);
			binaryString += s;
		}
	}

	//std::cout << binaryString << std::endl;
	return true;
}

void parser::parseString(std::string input, unsigned int maxLength)
{
	objects.clear();
	
	std::cout << "Input string: " << input << std::endl;

	if (!prepareString(input, maxLength)) return;

	binaryString = leftOver + binaryString;
	std::cout << "Input binary string: " << binaryString << std::endl;

	leftOver.clear();

	//parsing actual binary string that we prepared earlier
	std::string checker;
	std::string buffer;
	std::string garbage;

	while (binaryString.length() > 7)
	{
		checker = binaryString.substr(0, 8);
		
		if (checker == "11111111")
		{
			if (garbage.length() > 0)
			{
				objects.push_back(bitObject(4, garbage));
				garbage.clear();
			}

			buffer = checker;
			int oneCounter = 8;
			for (int i = 8; i < binaryString.length(); i++)
			{
				if (i == binaryString.length() - 1)
				{
					//leftOver += binaryString;
					//binaryString.clear();
					buffer += binaryString[i];
					objects.push_back(bitObject(1, buffer));

					binaryString.clear();
					break;
				}
				if (binaryString[i] != '1')
				{
					objects.push_back(bitObject(1, buffer));
					binaryString = binaryString.substr(buffer.length(), binaryString.length() - buffer.length());
					break;
				}
				oneCounter++;
				buffer += binaryString[i];
			}
		}
		else if (checker == "01111110")
		{
			int counter = 1;
			int anchor = 8;
			if (garbage.length() > 0)
			{
				objects.push_back(bitObject(4, garbage));
				garbage.clear();
			}

			std::size_t index = binaryString.find("01111110", anchor);
			//binaryString = binaryString.substr(8, binaryString.length() - 8);
			//std::cout << "Index is: " << index << std::endl;

			while (index == anchor)
			{
				//std::cout << "Index is: " << index << std::endl;
				if (index != std::string::npos)
				{
					if (index == anchor)
					{
						counter++;
						anchor += 8;
					}
				}
				index = binaryString.find("01111110", anchor);
			} 

			std::string s = binaryString.substr(anchor - 8, index - (anchor - 16));
			//std::cout << "Packet string: " << s << std::endl;
			if (index != std::string::npos)
			{
				if (bitObject::isValidPacket(s))
				{
					objects.push_back(bitObject(2, binaryString.substr(0, anchor - 8)));
					//binaryString = binaryString.substr(anchor - 8, binaryString.length() - anchor + 8);
					objects.push_back(bitObject(3, s));
					binaryString = binaryString.substr(index + 8, binaryString.length() - index);

					std::cout << binaryString << std::endl;
				}
				else
				{
					objects.push_back(bitObject(2, binaryString.substr(0, anchor + 8)));
					binaryString = binaryString.substr(anchor + 8, binaryString.length() - (anchor + 8));
				}
			}
			else
			{
				std::string s = binaryString.substr(0, anchor);
				binaryString = binaryString.substr(anchor, binaryString.length() - anchor);
				objects.push_back(bitObject(2, s));
			}
		}
		else if (binaryString.length() == 8)
		{
			//leftOver.clear();
			//leftOver = garbage;
			//leftOver += binaryString;
			garbage += binaryString;

			objects.push_back(bitObject(4, garbage));

			binaryString.clear();
			garbage.clear();
		}
		else
		{
			garbage += binaryString[0];
			binaryString.erase(0, 1);
		}

	}

	//leftOver.clear();
	//leftOver = binaryString;
	std::cout << "Leftover: " << leftOver << std::endl;
}

std::string parser::getParsed()
{
	std::string r;
	for (int i = 0; i < objects.size(); i++)
	{
		r += "\nBinary data: " + objects[i].data;
		r += "\nHex data: " + objects[i].getValue();
		r += " ";
	}
	return r;
}

parser::~parser()
{
}
