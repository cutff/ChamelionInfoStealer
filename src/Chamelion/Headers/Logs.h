#include "Includes.h"
#include "Timing.h"
#pragma once

//Logs Interface 
struct Logs : Timing {
	virtual ~Logs() = default;
	Logs(){
		//Random Name Generation for log file
	}
	//virtual bool GenerateLogFile();
	virtual bool OutputFile(const std::string& message, const std::string& path) = 0;
	virtual bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept = 0;
};