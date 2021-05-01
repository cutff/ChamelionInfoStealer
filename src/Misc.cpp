#include "Misc.h"

bool SCH::LockBackground() {
	HKEY LH_LOCKBACKGROUND;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies", 0, KEY_WRITE, &LH_LOCKBACKGROUND) != ERROR_SUCCESS) {
#ifdef _DEBUG
		std::cout << "Failed to open Registry Key : SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies" << std::endl;
#endif
		return false;
	}

	WCHAR value[] = L"1";
	if (RegSetValueExW(LH_LOCKBACKGROUND, TEXT("NoChangingWallPaper"), 0, REG_EXPAND_SZ, (BYTE*)&value, sizeof(value)) != ERROR_SUCCESS) {
#ifdef _DEBUG
		std::cout << "Failed to create new key NoChangingWallPaper" << std::endl;
#endif
		return false;
	}
#ifdef _DEBUG
	std::cout << "Wallpaper key created !" << std::endl;
#endif
	return true;
}