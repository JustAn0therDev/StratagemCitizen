#include <iostream>
#include <fstream>
#include "StratagemConfigParser.h"

Stratagem StratagemConfigParser::GetStratagemFromFileLine(std::string& p_FileLine)
{
	std::string stratagemName;
	std::vector<Arrow> arrows;
	std::string imagePath;

	size_t propertyIndex = 0;
	size_t position = 0;
	std::string delimiter = "\t";
	std::string token;

	while ((position = p_FileLine.find(delimiter)) != std::string::npos)
	{
		token = p_FileLine.substr(0, position);
		
		if (propertyIndex == 0)
		{
			stratagemName = token;
		}
		else if (propertyIndex == 1)
		{
			std::string arrowDelimiter = ",";

			size_t pos = 0;
			std::string arrowToken;
			
			while ((pos = token.find(arrowDelimiter)) != std::string::npos) {
				arrowToken = token.substr(0, pos);
				
				KeyboardKey keyboardKey = (KeyboardKey)0;
				std::string image;

				if (arrowToken == "UP")
				{
					keyboardKey = KEY_UP;
					image = "Assets/Arrow Up.png";
				}
				else if (arrowToken == "LEFT")
				{
					keyboardKey = KEY_LEFT;
					image = "Assets/Arrow Left.png";
				}
				else if (arrowToken == "RIGHT")
				{
					keyboardKey = KEY_RIGHT;
					image = "Assets/Arrow Right.png";
				}
				else if (arrowToken == "DOWN")
				{
					keyboardKey = KEY_DOWN;
					image = "Assets/Arrow Down.png";
				}

				arrows.push_back(Arrow(image.c_str(), keyboardKey));
				token.erase(0, pos + delimiter.length());
			}

			arrowToken = token.substr(0, pos);
			
			KeyboardKey keyboardKey = (KeyboardKey)0;
			std::string image;

			if (arrowToken == "UP")
			{
				keyboardKey = KEY_UP;
				image = "Assets/Arrow Up.png";
			}
			else if (arrowToken == "LEFT")
			{
				keyboardKey = KEY_LEFT;
				image = "Assets/Arrow Left.png";
			}
			else if (arrowToken == "RIGHT")
			{
				keyboardKey = KEY_RIGHT;
				image = "Assets/Arrow Right.png";
			}
			else if (arrowToken == "DOWN")
			{
				keyboardKey = KEY_DOWN;
				image = "Assets/Arrow Down.png";
			}

			arrows.push_back(Arrow(image.c_str(), keyboardKey));
		}

		p_FileLine.erase(0, position + delimiter.length());
		propertyIndex++;
	}

	imagePath = p_FileLine.substr(0, position);
	return Stratagem(stratagemName.c_str(), arrows, ("Assets/" + imagePath).c_str());
}

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
	// TODO: Read the file and parse its contents
	std::ifstream file(m_FilePath);
	std::string line;

	if (file.is_open()) 
	{
		while (std::getline(file, line)) 
		{
			m_Stratagems.push_back(GetStratagemFromFileLine(line));
		}
	}
}

std::vector<Stratagem> StratagemConfigParser::GetStratagems() const
{
	return m_Stratagems;
}

