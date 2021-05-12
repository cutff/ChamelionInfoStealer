#include "Includes.h"
#include "lm.h"
#include <cassert>
#pragma comment(lib, "netapi32.lib")
#pragma once

struct NetUsers { //Will switch to a class if i need to use private members.
	std::vector<std::string> UserList;
	bool GetNetUsers();
};