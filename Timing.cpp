#include <chrono> //chrono
#include <sstream> //sstream
#include <iomanip> //put_time
#include "Timing.h"

std::string Timing::GetCurrentComputerTime() {
	std::chrono::system_clock::time_point c_time = std::chrono::system_clock::now();
	auto cTimeToTimeT = std::chrono::system_clock::to_time_t(c_time);
	std::stringstream ss;
	struct tm timeinfo;
	ss << std::put_time(std::localtime(&cTimeToTimeT), "%Y-%m-%d %X");
	return ss.str();
}