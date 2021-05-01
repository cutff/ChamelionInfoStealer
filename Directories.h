#include "Includes.h"
#pragma once


struct Directories {
	std::wstring p_Desktop = L"";
	std::wstring p_Documents = L"";
	std::wstring p_Temp = L"";
	std::wstring p_AppData = L"";
	std::wstring p_FirefoxAppData = L"";
	std::wstring p_User = L"";
	bool GetDirectoryList();
};