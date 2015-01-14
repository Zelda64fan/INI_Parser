// INI_Parser.h
// Project:
// Last updated: 2015-01-13 by Adam Armbrester: first version
// Implementation of INI_Parser.h

#include "INI_Parser.h"
#include <fstream>
#include <iostream>

INI_Parser::INI_Parser() {

}

INI_Parser::~INI_Parser() {
	Unload();
}

char INI_Parser::ReadFile(std::string file) {
	// If no headers are found, we return 2
	bool found_headers = false;

	// Buffers for temporarily holding stuff
	std::string header_buf = "";
	std::string key_buf = "";
	std::string value_buf = "";
	std::string line_buf = "";

	std::ifstream fin;
	char c;
	fin.open(file.c_str());
	
	if (!fin) {
		return INI_READ_COULDNT_OPEN;
	}

	while (!fin.eof()) {
		getline(fin, line_buf);

		// Skip comments and blank lines
		if (line_buf[0] == '#' || line_buf == "")
			continue;
		
		if (line_buf[0] == '[') {    // Start of a new header
			found_headers = true;
			header_buf = line_buf;
			// Remove the ] at the end; if it doesn't exist, the file is
			// malformed
			if (header_buf[header_buf.length() - 1] != ']')
				return INI_READ_MALFORMED;
			else
				header_buf = header_buf.substr(1, header_buf.length() - 2);
		} else if (header_buf == "")   // Return if there's a key with no header
			return INI_READ_KEY_WITH_NO_HEADER;
		else { // Start of a key
			key_buf = "";
			
			// Read up to the = to get the key name. If there is no =, the file
			// is malformed.
			unsigned int valueStart = 0;   // Where the = is
			for (unsigned int i = 0; i < line_buf.length(); i++) {
				if (line_buf[i] == '=') {
					valueStart = i;
					break;
				}
				key_buf += line_buf[i];
			}

			// If it's 0, no = was found
			value_buf = "";
			if (valueStart == 0)
				return INI_READ_MALFORMED;
			else if (valueStart < line_buf.length() - 1)  // Key is not empty
				for (unsigned int i = valueStart + 1; i < line_buf.length(); i++)
					value_buf += line_buf[i];

			// If we made it this far, everything must be good
			keymap[header_buf][key_buf] = value_buf;	
		}
	}

	if (!found_headers)
		return INI_READ_NO_HEADERS;
	else
		return INI_READ_SUCCESS;

}

bool INI_Parser::HeaderExists(std::string header) {
	return (keymap.count(header) != 0);
}

bool INI_Parser::KeyExists(std::string header, std::string key) {
	if (!HeaderExists(header)) {
		throw HeaderNotFoundException(header);
		return false;
	} else
		return (keymap[header].count(key) != 0);
}

std::string INI_Parser::GetKeyValue(std::string header, std::string key) {
	if (!HeaderExists(header)) {
		throw HeaderNotFoundException(header);
		return "";
	} else if (!KeyExists(header, key)) {
		throw KeyNotFoundException(header, key);
		return "";
	} else
		return keymap[header][key];
}

void INI_Parser::Unload() {
	keymap.clear();
}

// EOF
