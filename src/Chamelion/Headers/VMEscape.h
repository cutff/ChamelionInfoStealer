#include "Includes.h"
#pragma once

namespace VMEscape {
	void virtualBoxEscape() {
		DWORD fileAttribute = GetFileAttributesA("C:\\Windows\\System32\\Drivers\\VBoxMouse.sys");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\VBoxGuest.sys");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\VBoxSF.sys");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\VBoxVideo.sys");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxdisp.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxhook.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxmrxnp.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxogl.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglarrayspu.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglcrutil.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglerrorspu.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglfeedbackspu.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglpackspu.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\vboxoglpassthroughspu.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
	}
	void VMWareEscape() {
		DWORD fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\Vmmouse.sys");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vm3dgl.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vmdum.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vm3dver.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vmtray.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\VMToolsHook.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vmmousever.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vmhgfs.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\vmGuestLib.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Drivers\\VmGuestLibJava.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
		fileAttribute = GetFileAttributesA("C:\\windows\\System32\\Driversvmhgfs.dll");
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && !(fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) exit(EXIT_FAILURE);
	}
}
