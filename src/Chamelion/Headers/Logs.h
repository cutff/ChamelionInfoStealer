#include "Includes.h"
#include "Timing.h"
#pragma once

//We're going to try to achieve runtime polymorphism using pure virtual class.
struct Logs : Timing {
	virtual ~Logs() = default;
	//virtual bool GenerateLogFile();
	virtual bool OutputFile(const std::string& message, const std::string& path) = 0;
	virtual bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept = 0;
};