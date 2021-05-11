#include <chrono> //chrono
#include <sstream> //sstream
#include <iomanip> //put_time
#include "../Headers/Timing.h"

std::string Timing::GetCurrentComputerTime() {
	std::chrono::system_clock::time_point c_time = std::chrono::system_clock::now();
	auto cTimeToTimeT = std::chrono::system_clock::to_time_t(c_time);
	std::stringstream ss;
	struct tm timeinfo;
	ss << std::put_time(std::localtime(&cTimeToTimeT), "%Y-%m-%d %X");
	return ss.str();
}

unsigned int Timing::GetCurrentTimestamp() {
	const std::chrono::system_clock::time_point timestamp = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
}