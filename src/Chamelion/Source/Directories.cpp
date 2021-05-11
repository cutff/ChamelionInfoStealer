#include "../Headers/Directories.h"
#include <ShlObj.h>
#include <shlobj_core.h>
#include <sstream>

std::wstring concatenatePath(wchar_t* userMainDir, std::wstring contentToConcat) {
	std::wstringstream wss;
	wss << userMainDir << contentToConcat;
	return wss.str();
}

bool checkPath(const std::wstring pathTocheck) {
	DWORD pathAttribute = GetFileAttributesW(pathTocheck.c_str());
	if (pathAttribute != INVALID_FILE_ATTRIBUTES && (pathAttribute & FILE_ATTRIBUTE_DIRECTORY)) return true;

	return false;
}

bool Directories::GetDirectoryList() {
	wchar_t driveName[MAX_PATH];
	GetModuleFileNameW(NULL, driveName, MAX_PATH);
	wchar_t driveLetter = driveName[0];

	wchar_t* userMainDir = nullptr;
	//UserMain Path
	if (SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &userMainDir) != S_OK) return false;
	this->p_User = userMainDir;
	//OtherDirs
	try {
		if (checkPath(concatenatePath(userMainDir, L"\\AppData"))) this->p_AppData = concatenatePath(userMainDir, L"\\AppData");
		if (checkPath(concatenatePath(userMainDir, L"\\Desktop"))) this->p_Desktop = concatenatePath(userMainDir, L"\\Desktop");
		if (checkPath(concatenatePath(userMainDir, L"\\Documents"))) this->p_Documents = concatenatePath(userMainDir, L"\\Documents");
		if (checkPath(concatenatePath(userMainDir, L"\\AppData\\Local\\Temp"))) this->p_Temp = concatenatePath(userMainDir, L"\\AppData\\Local\\Temp");
		if (checkPath(concatenatePath(userMainDir, L"\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles"))) this->p_FirefoxAppData = concatenatePath(userMainDir, L"\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles");
#ifdef _DEBUG
		std::wcout << this->p_AppData << std::endl;
		std::wcout << this->p_Desktop << std::endl;
		std::wcout << this->p_Documents << std::endl;
		std::wcout << this->p_Temp << std::endl;
		std::wcout << this->p_User << std::endl;
		std::wcout << this->p_FirefoxAppData << std::endl;
#endif
	}
	catch (...) {
		return false;
	}

	return true;
}