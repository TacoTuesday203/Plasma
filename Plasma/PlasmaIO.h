#pragma once
#include "Plasma.h"
#include <fstream>
#include <vector>

namespace Plasma {
	class IO
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}

