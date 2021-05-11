#include "Printers.h"

/// <summary>
/// reinterpretPrinterValueAddress is used to reintepret the pointer address of the values enumerated by EnumPrinters.
/// </summary>
/// <param name="printerInformation">LPPRINTER_INFO_2 Value</param>
/// <returns>The same value but reinterpreted as a std::string</returns>
std::string reinterpretPrinterValueAddress(LPWSTR& printerInformation) {
	std::string printersReinterpreted;
	for (int i = 0; i < wcslen(printerInformation); i++) {
		printersReinterpreted.append(reinterpret_cast<const char*>(printerInformation + i));
	}
	return printersReinterpreted;
}

bool Printers::EnumeratePrintersInformation() {
	LPPRINTER_INFO_2 printerInformation = nullptr;
	DWORD pcbNeeded, pcReturned = { 0 }; //pcbNeeded : A pointer to a value that receives the number of bytes copied
									 //pcbReturned : A pointer to a value that received the number of PRINTER_INFO_5.
	//Get Buffer Size
	EnumPrinters(
		PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
		NULL,
		2,
		(PBYTE)0,
		0,
		&pcbNeeded,
		&pcReturned
	);

	//Allocate memory for LPPRINTER_INFO_2
	if ((printerInformation = (LPPRINTER_INFO_2)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, pcbNeeded)) == 0) exit(EXIT_FAILURE); //Exit Failure if not enough memory is available.
	//Enum our printers
	if (EnumPrinters(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, (LPBYTE)printerInformation, pcbNeeded, &pcbNeeded, &pcReturned) == 0) {
		std::cout << "ENUMPRINTERS FAILED WITH ERROR : " << GetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}


	for (DWORD dwItem = 0; dwItem < pcReturned; dwItem++) {
#ifdef _DEBUG
		std::cout << "Printer Name : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pPrinterName) << std::endl;
		printerInformation[dwItem].Attributes& PRINTER_ATTRIBUTE_SHARED ?
			std::cout << "Share Name : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pShareName) << std::endl :
			std::cout << "Share Name : NONE" << std::endl;

		std::cout << "Ports : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pPortName) << std::endl;
		std::cout << "Driver Name : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pDriverName) << std::endl;
		std::cout << "Comment : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pComment) << std::endl;
		std::cout << "Location : " << reinterpretPrinterValueAddress(printerInformation[dwItem].pLocation) << std::endl << std::endl;
#endif
		//If printInformation has attributes PRINTER_ATTRIBUTE_SHARED then push it into our struct vector else we push "NONE"
		printerInformation[dwItem].Attributes& PRINTER_ATTRIBUTE_SHARED ?
			Printers.push_back({
				reinterpretPrinterValueAddress(printerInformation[dwItem].pPrinterName),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pShareName), //PUSH SHARE NAME
				reinterpretPrinterValueAddress(printerInformation[dwItem].pPortName),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pDriverName),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pComment),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pLocation)
				}) : 
			Printers.push_back({
				reinterpretPrinterValueAddress(printerInformation[dwItem].pPrinterName),
				"NONE", //Push NONE
				reinterpretPrinterValueAddress(printerInformation[dwItem].pPortName),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pDriverName),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pComment),
				reinterpretPrinterValueAddress(printerInformation[dwItem].pLocation)
				});
	}
	return true;
}