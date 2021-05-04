#include "Includes.h"
#pragma once

namespace Registers {
	struct Key {
		std::vector<std::string> subKeys;
	};
	Key RegEnumSubKeys(HKEY key, const char* subKey);
	void EnumerateValues(HKEY key, DWORD nValues);
	std::string KeyGetValue(const char* keyPath, const char* keyName);
}