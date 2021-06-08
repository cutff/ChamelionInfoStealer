#include "Includes.h"
#include "lm.h"
#include "Logs.h"
#include <cassert>
#pragma comment(lib, "netapi32.lib")
#pragma once

struct NetUserInformation{
	std::string UserName;
	std::vector<std::string> UserGroups;
};

struct NetUsers : public Logs { //Will switch to a class if i need to use private members.
	std::vector<NetUserInformation> UserList;
	bool GetNetUsers();
	bool GetNetGroups();
	///LOGS Interface implementation
	bool OutputFile(const std::string& message, const std::string& path) override;
	bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept override;
	
};