// INI_Parser.h
// Project:
// Last updated: 2015-01-13 by Adam Armbrester: Changed "header" to "section" to
// 	reflect correct terminology, made sections & keys be stored & processed in
// 	lowercase so case won't matter anymore.
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
	// If no sections are found, we return 2
	bool found_sections = false;

	// Buffers for temporarily holding stuff
	std::string section_buf = "";
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
		if (line_buf[0] == ';' || line_buf[0] == '#' || line_buf == "")
			continue;
		
		if (line_buf[0] == '[') {    // Start of a new section
			found_sections = true;
			section_buf = line_buf;
			// Remove the ] at the end; if it doesn't exist, the file is
			// malformed
			if (section_buf[section_buf.length() - 1] != ']')
				return INI_READ_MALFORMED;
			else
				section_buf = section_buf.substr(1, section_buf.length() - 2);
		} else if (section_buf == "")   // Return if there's a key with no section
			return INI_READ_KEY_WITH_NO_SECTION;
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

			// If we made it this far, everything must be good. We'll convert to
			// lowercase first, since these should not be case sensitive
			std::transform(section_buf.begin(), section_buf.end(),
				section_buf.begin(), ::tolower);
			std::transform(key_buf.begin(), key.end(), key_buf.begin(),
				::tolower);
			keymap[section_buf][key_buf] = value_buf;	
		}
	}

	if (!found_sections)
		return INI_READ_NO_SECTIONS;
	else
		return INI_READ_SUCCESS;

}

bool INI_Parser::SectionExists(std::string section) {
	// Convert to lowercase, so case won't be an issue
	std::transform(section.begin(), section.end(),
		section.begin(), ::tolower);
	return (keymap.count(section) != 0);
}

bool INI_Parser::KeyExists(std::string section, std::string key) {
	// Convert to lowercase
	std::transform(section.begin(), section.end(),
		section.begin(), ::tolower);
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);

	if (!SectionExists(section)) {
		throw SectionNotFoundException(section);
		return false;
	} else
		return (keymap[section].count(key) != 0);
}

std::string INI_Parser::GetKeyValue(std::string section, std::string key) {
	// Convert to lowercase
	std::transform(section.begin(), section.end(),
		section.begin(), ::tolower);
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);

	if (!SectionExists(section)) {
		throw SectionNotFoundException(section);
		return "";
	} else if (!KeyExists(section, key)) {
		throw KeyNotFoundException(section, key);
		return "";
	} else
		return keymap[section][key];
}

void INI_Parser::Unload() {
	keymap.clear();
}

// EOF
