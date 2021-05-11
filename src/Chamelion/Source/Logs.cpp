#include "../Headers/Logs.h"


bool Logs::OutputFile(const std::string& message, const std::string& path) {
	try {
		std::ofstream oLogFile{};
		oLogFile.open(path, std::ios::app);
		oLogFile << GetCurrentComputerTime() << " | " << message;
		oLogFile.close();
	}
	catch (std::runtime_error& e) {
		return false;
	}
	catch (std::exception& e) {
		return false;
	}
	catch (...) {
		return false;
	}
	return true;
}