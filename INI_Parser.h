// INI_Parser.h
// Project:
// Last updated: 2015-01-13 by Adam Armbrester: Changed "header" to "section" to
// 	reflect correct terminology, made sections & keys be stored & processed in
// 	lowercase so case won't matter anymore.
// Used to read and parse .ini files formatted like this:
// 	[Section A]
// 	key0=value0
// 	key1=value1
// 	; Lines starting with a ; or # are comments
// 	[Section B]
// 	key0=value0
// 	key1=value1
// The contents of the file are read into two nested std::maps all at once. Key
// values are returned as std::strings.
// You can check that a section exists with SectionExists(sectionTitle), and
// check keys with KeyExists(sectionTitle, keyTitle). Key values can be read
// with GetKeyValue(sectionTitle, keyTitle).
// Errors:
// 	SectionNotFoundException: the specified section doesn't exist. Has a
// 		GetName() function.
// 	KeyNotFoundException: the specified key doesn't exist Not thrown if the
// 		above is thrown. Has GetName() and GetSectionName() functions.
#include <map>
#include <string>

#ifndef INI_PARSER_H
#define INI_PARSER_H

const char INI_READ_SUCCESS = 0;
const char INI_READ_COULDNT_OPEN = 1;
const char INI_READ_MALFORMED = 2;
const char INI_READ_NO_SECTIONS = 3;
const char INI_READ_KEY_WITH_NO_SECTION = 4;

class INI_Parser {
public:
	/** Generic constructor */
	INI_Parser();
	
	/** Generic destructor */
	~INI_Parser();

	/** Read the specified file into memory, so its contents can be processed.
	 * Returns 0 on success and 1, 2, or 3 if something goes wrong (see
	 * INI_READ_* consts for specific errors)
	 * \return INI_READ_SUCCESS, INI_READ_NOT_FOUND, or INI_READ_NO_SECTIONS,
	 */
	char ReadFile(std::string file);

	/** Check if the specified section exists.
	 * \param section The section to look for.
	 * \return true if the section exists, false if it doesn't.
	 */
	bool SectionExists(std::string section);

	/** Check if the specified key exists in the specified section. Will throw
	 * SectionNotFoundException if the section doesn't exist.
	 * \param section The section to look in.
	 * \param key The name of the key to look for.
	 * \return true if the section exists, false if it doesn't.
	 */
	bool KeyExists(std::string section, std::string key);

	/** Get the value of a particular key from a particular section, as an
	 * std::string. Will throw SectionNotFoundException if the section doesn't
	 * exist, and KeyNotFoundException if the key doesn't.
	 * \param section The section to look in.
	 * \param key The name of the key whose value to get.
	 * \return The key's value, as an std::string.
	 */
	std::string GetKeyValue(std::string section, std::string key);

	/** Clears the file contents from memory. To access it again, the file must
	 * be re-read with ReadFile().
	 */
	void Unload();

private:
	// Each key represents a section: its value is another map, whose keys are
	// the keys for that section.
	std::map<std::string, std::map<std::string, std::string> > keymap;
};

// Section not found
class SectionNotFoundException {
public:
	SectionNotFoundException(std::string name) {
		_name = name;
	}

	~SectionNotFoundException() {
		_name = "";
	}

	std::string GetName() {
		return _name;
	}

private:
	std::string _name;
};

// Key not found
class KeyNotFoundException {
public:
	KeyNotFoundException(std::string section, std::string name) {
		_section = section;
		_name = name;
	}

	~KeyNotFoundException() {
		_section = "";
		_name = "";
	}

	std::string GetSectionName() {
		return _section;
	}

	std::string GetName() {
		return _name;
	}

private:
	std::string _section;
	std::string _name;
};
#endif
// EOF
