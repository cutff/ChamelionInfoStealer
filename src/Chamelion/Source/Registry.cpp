#include "../Headers/Registry.h"

std::string Registers::KeyGetValue(const char* keyPath, const char* keyName) {
	char buffer[255];
	DWORD BufferSize = BUFFER;
	std::string retValue = "";
	if (RegGetValueA(HKEY_LOCAL_MACHINE, keyPath, keyName, RRF_RT_ANY, NULL, (PVOID)&buffer, &BufferSize) != ERROR_SUCCESS) {
#ifdef _DEBUG
		std::cout << "Failed to obtain value for key : " << keyPath << "\\" << keyName << std::endl;
#endif
	}
#ifdef _DEBUG
	std::cout << keyName << " : " << buffer << std::endl;
#endif
	return buffer;
}

void Registers::EnumerateValues(HKEY key, DWORD nValues) {
	DWORD dwIndex = 0;
	LPSTR valueName = new CHAR[64];
	DWORD valNameLen = NULL;
	DWORD dataType = NULL;
	BYTE data[1024];
	DWORD dataSize = 1024;

	for (int i = 0; i < nValues; i++) {
		if (RegEnumValueA(key, dwIndex, valueName, &valNameLen, NULL, &dataType, data, &dataSize) != ERROR_SUCCESS) {
			std::cout << "ERROR ENUMERATING VALUES" << std::endl;
			return;
		}
		std::cout << "Value : " << data;
		dwIndex++;
	}
}

Registers::Key Registers::RegEnumSubKeys(HKEY key, const char* subKey) {
	Key sRet;
	HKEY hKey; //Hkey used in RegOpenKeyEx
	DWORD SubKeys; //Number of subkeys
	DWORD maxSubKeyLen; //Longest subkey name length
	DWORD cValues; //Number of values for key
	DWORD maxValueLen; //Longest value name length
	DWORD retCode; //Return values
	LSTATUS Result; //Result

	if (RegOpenKeyExA(key, subKey, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ, &hKey) != ERROR_SUCCESS) {
		#ifdef _DEBUG
				std::cout << "[-] ERROR with RegOpenKeyExA" << std::endl;
		#endif
	}

	if (RegQueryInfoKey(
		hKey, //Key Handle (HKEY)
		NULL, //Class name buffer
		NULL, //Size for class string
		NULL, //reserved
		&SubKeys, //number of subkeys
		&maxSubKeyLen, //longest subkey length
		NULL, //longest class string
		&cValues, //number of values for this key
		&maxValueLen, //longest value name
		NULL,
		NULL,
		NULL) != ERROR_SUCCESS) {
#ifdef _DEBUG
		std::cout << "[-] ERROR with RegQueryInfoKey !" << std::endl;
#endif
	}
#ifdef _DEBUG
	//Log Success Querying Key
	//std::cout << "Success Querying Key !" << std::endl;
#endif
	if (SubKeys > 0) {
		char currentSubkey[MAX_PATH];
		for (int i = 0; i < SubKeys; i++) {
			DWORD currentSubkeyLen = MAX_PATH; //260
			if (RegEnumKeyExA(
				hKey, //Handle to open predefined key
				i, //Index of the subkey to retrieve.
				currentSubkey, //Buffer to receives the name of the subkey
				&currentSubkeyLen, //Size of the buffer
				NULL, //Reserved
				NULL, //Buffer for class string
				NULL, //Size of that buffer
				NULL) != ERROR_SUCCESS) //Last write time
			{
#ifdef _DEBUG
				std::cout << "ERROR with enumerating subkey" << std::endl;
#endif
			}
			//std::cout << currentSubkey << std::endl;
			std::string s_sKey = currentSubkey;
			sRet.subKeys.push_back(s_sKey);
		}
	}
	else {
		Registers::EnumerateValues(hKey, cValues);
	}
	RegCloseKey(hKey);
	return sRet;
}