#include "StringFunctions.h"

const std::vector<std::string> StringFunctions::Split(std::string input, const std::string delimiter)
{
	size_t pos = 0;
	std::vector<std::string> tokens;
	
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(input.substr(0, pos));
		input.erase(0, pos + delimiter.length());
	}

	tokens.push_back(input.substr(0, pos));

	return tokens;
}
