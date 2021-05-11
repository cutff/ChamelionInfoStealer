#include "Includes.h"
#include <winspool.h>
#pragma once

struct PrinterInformations {
	std::string PrinterName;
	std::string PrinterShareName;
	std::string PrinterPorts;
	std::string PrinterDriverName;
	std::string Comment;
	std::string Location;
};

struct Printers {
	std::vector<PrinterInformations> Printers;
	bool EnumeratePrintersInformation();
};
