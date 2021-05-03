#include "Includes.h"
#include "Timing.h"
#pragma once

struct Logs : Timing {
	std::string currentLogPath = "";
	bool GenerateLogFile();
	bool OutputFile(const std::string& message, const std::string& path);
	bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept;
};