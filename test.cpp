// File: main.cpp
// Project: INI Parser class (test file)
// Last update: 2015-01-13 by Adam Armbrester: first version
// A test implementation of the INI_Parser class.
// TODO: Clean this up?

#include "INI_Parser.h"
#include <iostream>
#include <map>
#include <string>

int main() {
	INI_Parser ip;
	int error = ip.ReadFile("testFile.ini");
	if (error != INI_READ_SUCCESS) {
		std::cout << "Read error " << error << std::endl;
		return error;
	}

	// Checking validity with if/else
	std::cout << "Section \"Settings\" does ";
	if (ip.SectionExists("Settings")) {
		std::cout << "exist" << std::endl;
		
		std::cout << "\tKey Settings/thing1 ";
		if (ip.KeyExists("Settings", "thing1")) {
			std::cout << "exists and is " << ip.GetKeyValue("Settings",
				"thing1") << std::endl;
		} else 
			std::cout << "does not exist" << std::endl;

		std::cout << "\tKey Settings/thing2 ";
		if (ip.KeyExists("Settings", "thing2")) {
			std::cout << "exists and is " << ip.GetKeyValue("Settings",
				"thing2") << std::endl;
		} else 
			std::cout << "does not exist" << std::endl;

		std::cout << "\tKey Settings/thing3 ";
		if (ip.KeyExists("Settings", "thing3")) {
			std::cout << "exists and is " << ip.GetKeyValue("Settings",
				"thing3") << std::endl;
		} else 
			std::cout << "does not exist" << std::endl;

	} else 
		std::cout << "NOT exist" << std::endl;

	std::cout << "Section \"Data\" does ";
	if (ip.SectionExists("Data")) {
		std::cout << "exist" << std::endl;

		std::cout << "\tKey Data/info1 ";
		if (ip.KeyExists("Data", "info1")) {
			std::cout << "exists and is " << ip.GetKeyValue("Data",
				"info1") << std::endl;
		} else 
			std::cout << "does not exist" << std::endl;

		std::cout << "\tKey Data/info2 ";
		if (ip.KeyExists("Data", "info2")) {
			std::cout << "exists and is " << ip.GetKeyValue("Data",
				"info2") << std::endl;
		} else 
			std::cout << "does not exist" << std::endl;

	} else
		std::cout << "NOT exist" << std::endl;

	std::cout << "Section \"Nonexistent\" does ";
	if (!ip.SectionExists("Nonexistent"))
		std::cout << "NOT ";
	std::cout << "exist" << std::endl;

	// Checking with try/catch: quick example
	try {
		std::cout << "Nonexistent/nope = " << ip.GetKeyValue("Nonexistent",
			"nope") << std::endl;
	} catch (SectionNotFoundException h) {
		std::cout << "Section " << h.GetName() << " wasn't found" << std::endl;
	} catch (KeyNotFoundException k) {
		std::cout << "Key " << k.GetSectionName() << "/" << k.GetName() <<
			" wasn't found" << std::endl;
	}

	try {
		std::cout << "Settings/nope = " << ip.GetKeyValue("Settings",
			"nope") << std::endl;
	} catch (SectionNotFoundException h) {
		std::cout << "Section " << h.GetName() << " wasn't found" << std::endl;
	} catch (KeyNotFoundException k) {
		std::cout << "Key " << k.GetSectionName() << "/" << k.GetName() <<
			" wasn't found" << std::endl;
	}

	return 0;
}

//EOF
