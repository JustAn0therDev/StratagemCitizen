#pragma once
#include <vector>
#include "Stratagem.h"

class StratagemConfigParser
{
private:
	const char* m_FilePath;
	std::vector<Stratagem> m_Stratagems;
	Stratagem GetStratagemFromFileLine(std::string& line);
	Arrow GetArrowFromStratagemToken(std::string token);

public:
	StratagemConfigParser(const char* p_FilePath);
	void ParseStratagems();
	std::vector<Stratagem> GetStratagems() const;
};

