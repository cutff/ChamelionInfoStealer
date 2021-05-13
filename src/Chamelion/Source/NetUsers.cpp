#include "../Headers/NetUsers.h"
bool NetUsers::GetNetUsers() {
	LPUSER_INFO_0 pBuf = NULL; //Buffer
	LPUSER_INFO_0 pTmpBuf; //Temp Buffer
	DWORD dwLevel = 0; //Level 0
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH; //MAX_PREFEREND_LENGTH comes from lm.h headers and correspond to a (DWORD) -1
	DWORD dwEntriesRead = 0; //Number of "entries" (users).
	DWORD dwTotalEntries = 0; //Number of total "entries" (users).
	DWORD dwResumeHandle = 0;
	DWORD iterator; // DWORD iterator
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus; //NET_API_STATUS is a Double WORD (DWORD)
	LPTSTR pszServerName = NULL; //ServerName (in this case it's NULL)
	std::string TmpName;
	//Call the NetUserEnum Function, specifying level 0;
	//Enumerate global user account types only.
	do {
		nStatus = NetUserEnum(
			(LPCWSTR)pszServerName, //ServerName (in this case it's NULL)
			dwLevel, //Level 0
			FILTER_NORMAL_ACCOUNT, //Global Users
			(LPBYTE*)&pBuf, //Buffer
			dwPrefMaxLen,
			&dwEntriesRead, //Number of "entries" (users).
			&dwTotalEntries, //Number of total "entries" (users).
			&dwResumeHandle);

		if ((nStatus == NERR_Success) || nStatus == ERROR_MORE_DATA) {
			if ((pTmpBuf = pBuf) != NULL) {
				//Loop through the entries.
				for (iterator = 0; iterator < dwEntriesRead; iterator++) {
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL) {
						std::cout << "Access Violation Occured..." << std::endl;
						break;
					}
					//Push back the username to our UserList
					for (int i = 0; i < wcslen(pTmpBuf->usri0_name); i++) TmpName.append(reinterpret_cast<const char*>(pTmpBuf->usri0_name + i));
					this->UserList.push_back(TmpName);

					//Next loop
					TmpName.clear();
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}

	} while (nStatus == ERROR_MORE_DATA);

	return true;
}