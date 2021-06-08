#include "../Headers/NetUsers.h"

const DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH; //MAX_PREFEREND_LENGTH comes from lm.h headers and correspond to a (DWORD) -1
const DWORD dwLevel = 0; //Level 0 (We'll be using Level 0 all long so we put it const)
DWORD dwEntriesRead = 0; //Number of "entries" (users). 
DWORD dwTotalEntries = 0; //Number of total "entries" (users).
DWORD dwGroupsEntriesRead = 0;
DWORD dwGroupsTotalEntries = 0;

bool NetUsers::GetNetUsers() {
	NetUserInformation CurrentNetUser;
	LPUSER_INFO_0 pBuf = NULL; //Buffer
	LPUSER_INFO_0 pTmpBuf = NULL; //Temp Buffer
	//NetUsers Variables
	NET_API_STATUS nStatus; //NET_API_STATUS is a Double WORD (DWORD) used to store functions return value (state).
	DWORD dwResumeHandle = 0;
	DWORD iterator; // DWORD iterator
	DWORD dwTotalCount = 0;
	std::string TmpName = "";
	//NetGroups Variables
	NET_API_STATUS ngStatus; //NET_API_STATUS is a Double WORD (DWORD) used to store functions return value (state).
	LPGROUP_USERS_INFO_0 pGroupBuf = NULL;
	//Call the NetUserEnum Function, specifying level 0;
	//Enumerate global user account types only.
	do {
		nStatus = NetUserEnum(
			NULL, //ServerName (in this case it's NULL)
			dwLevel, //Level 0
			FILTER_NORMAL_ACCOUNT, //Global Users
			(LPBYTE*)&pBuf, //Buffer
			dwPrefMaxLen,
			&dwEntriesRead, //Number of "entries" (users).
			&dwTotalEntries, //Number of total "entries" (users).
			&dwResumeHandle);

		if (nStatus == NERR_Success || nStatus == ERROR_MORE_DATA) {
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
					std::cout << "[+] TmpName TRY : " << TmpName << std::endl;
					CurrentNetUser.UserName = TmpName;
					std::wcout << L"[+] User Found : " << pTmpBuf->usri0_name << std::endl;
					//Get our CurrentUser NetGroup
					std::cout << "Call to NetUserGetGroups" << std::endl;
					ngStatus = NetUserGetGroups(
						NULL, //Servername NULL since we want the local computer to be enum.
						pTmpBuf->usri0_name, //Our Current User name to enumerate
						dwLevel, //Same level as for the NetUserEnum Function which is level 0 which return the names of the global groups to which the user belongs.
						(LPBYTE*)pGroupBuf,
						dwPrefMaxLen,
						&dwGroupsEntriesRead,
						&dwGroupsTotalEntries
					);
					//Our call to NetUserGetGroups succeeded and we loop in our group list.
					std::cout << "111111ENUMERATING GROUPAASSSSSS" << std::endl;
					if(ngStatus == NERR_Success){
						std::cout << "ENUMERATING GROUPAASSSSSS" << std::endl;
						LPGROUP_USERS_INFO_0 pGroupTmpBuf;
						DWORD iterator;
						if((pGroupTmpBuf = pGroupBuf) != NULL){
							for(iterator = 0; iterator<dwGroupsEntriesRead ; iterator++){
								if(pTmpBuf == NULL){
									//Log that an access violation has occured.
									std::cout << "[+] Access Violation Occured when trying to get User Group" << std::endl;
									break;
								}
								std::wcout << L"[+] User has Groups : " << pGroupTmpBuf->grui0_name << std::endl;
								pTmpBuf++;
								dwTotalCount++;
							}
						} else {
							std::cout << "Can't Enum Groups !" << std::endl;
						}
					}
					this->UserList.push_back(CurrentNetUser);

					

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


bool NetUsers::GetNetGroups(){

	/*do {

	} while (nStatus == ERROR_MORE_DATA);*/
	return true;
}