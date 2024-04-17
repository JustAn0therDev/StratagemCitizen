#include <iostream>
#include <fstream>
#include "StratagemConfigParser.h"
#include "Utils.h"

StratagemConfigParser::StratagemConfigParser(const char* p_FilePath)
{
	if (p_FilePath == nullptr)
	{
		std::cout << "Stratagem config file path was null." << std::endl;
	}

	m_FilePath = p_FilePath;
}

void StratagemConfigParser::ParseStratagems()
{
	std::ifstream stratagemConfigFile(m_FilePath);

	if (stratagemConfigFile.is_open())
	{
		std::string line;
		while (std::getline(stratagemConfigFile, line))
		{
			m_Stratagems.push_back(GetStratagemFromFileLine(line));
		}
	}
}

Stratagem StratagemConfigParser::GetStratagemFromFileLine(std::string& p_FileLine)
{
	std::string stratagemName;
	std::vector<Arrow> arrows;
	std::string imagePath;

	size_t propertyIndex = 0;
	size_t position = 0;
	std::string delimiter = "\t";
	std::string token;

	Utils utils;

	const std::vector<std::string> stratagemTokens = utils.Split(p_FileLine, delimiter);

	for (auto& token : stratagemTokens)
	{
		if (propertyIndex == 0)
		{
			stratagemName = token;
		}
		else if (propertyIndex == 1)
		{
			const std::vector<std::string> arrowTokens = utils.Split(token, ",");

			for (auto& arrowToken : arrowTokens)
			{
				arrows.push_back(GetArrowFromStratagemToken(arrowToken));
			}
		}
		else if (propertyIndex == 2)
		{
			imagePath = token;
		}

		p_FileLine.erase(0, position + delimiter.length());
		propertyIndex++;
	}

	return Stratagem(stratagemName.c_str(), arrows, ("Assets/" + imagePath).c_str());
}

Arrow StratagemConfigParser::GetArrowFromStratagemToken(std::string token)
{
	KeyboardKey keyboardKey = (KeyboardKey)0;
	std::string image;

	if (token == "UP")
	{
		keyboardKey = KEY_UP;
		image = "Assets/Arrow Up.png";
	}
	else if (token == "LEFT")
	{
		keyboardKey = KEY_LEFT;
		image = "Assets/Arrow Left.png";
	}
	else if (token == "RIGHT")
	{
		keyboardKey = KEY_RIGHT;
		image = "Assets/Arrow Right.png";
	}
	else if (token == "DOWN")
	{
		keyboardKey = KEY_DOWN;
		image = "Assets/Arrow Down.png";
	}

	return Arrow(image.c_str(), keyboardKey);
}

std::vector<Stratagem> StratagemConfigParser::GetStratagems() const
{
	return m_Stratagems;
}

