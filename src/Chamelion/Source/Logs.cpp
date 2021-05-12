#include "../Headers/Logs.h"
#include "../Headers/Printers.h"
#include "../Headers/Browsers.h"
#include "../Headers/NetUsers.h"


//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS
//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS
//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS
//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS
//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS//PRINTERS

///LOGS INTERFACE IMPLEMENTATION
bool Printers::OutputFile(const std::string& message, const std::string& path) {
	try {
		std::ofstream oLogFile{};
		oLogFile.open(path, std::ios::app);
		oLogFile << GetCurrentComputerTime() << " | " << message;
		oLogFile.close();
	}
	catch (std::exception& e) {
		return false;
	}
	catch (...) {
		return false;
	}
	return true;
}

bool Printers::OutputEncryptedContent(const std::string& message, const std::string& path) noexcept {
	//Make Encryption routine and output encrypted content to log file.
	return true;
}

//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS
//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS
//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS
//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS
//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS
//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS//BROWSERS

///LOGS INTERFACE IMPLEMENTATION
bool Browsers::OutputFile(const std::string& message, const std::string& path) {
	try {
		std::ofstream oLogFile{};
		oLogFile.open(path, std::ios::app);
		oLogFile << GetCurrentComputerTime() << " | " << message;
		oLogFile.close();
	}
	catch (std::exception& e) {
		return false;
	}
	catch (...) {
		return false;
	}
	return true;
}

bool Browsers::OutputEncryptedContent(const std::string& message, const std::string& path) noexcept {
	//Make Encryption routine and output encrypted content to log file.
	return true;
}

//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS
//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS
//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS
//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS
//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS
//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS//NETUSERS

///LOGS INTERFACE IMPLEMENTATION
bool NetUsers::OutputFile(const std::string& message, const std::string& path) {
	try {
		std::ofstream oLogFile{};
		oLogFile.open(path, std::ios::app);
		oLogFile << GetCurrentComputerTime() << " | " << message;
		oLogFile.close();
	}
	catch (std::exception& e) {
		return false;
	}
	catch (...) {
		return false;
	}
	return true;
}

bool NetUsers::OutputEncryptedContent(const std::string& message, const std::string& path) noexcept {
	//Make Encryption routine and output encrypted content to log file.
	return true;
}