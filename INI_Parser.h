// INI_Parser.h
// Project:
// Last updated: 2015-01-13 by Adam Armbrester: first version
// Used to read and parse .ini files formatted like this:
// 	[Header A]
// 	key0=value0
// 	key1=value1
// 	# Lines starting with a # are comments
// 	[Header B]
// 	key0=value0
// 	key1=value1
// The contents of the file are read into two nested std::maps all at once. Key
// values are returned as std::strings.
// You can check that a header exists with HeaderExists(headerTitle), and check
// keys with KeyExists(headerTitle, keyTitle). Key values can be read with
// GetKeyValue(headerTitle, keyTitle).
// Errors:
// 	HeaderNotFoundException: the specified header doesn't exist. Has a GetName()
// 		function.
// 	KeyNotFoundException: the specified key doesn't exist Not thrown if the
// 		above is thrown. Has GetName() and GetHeaderName() functions.
#include <map>
#include <string>

#ifndef INI_PARSER_H
#define INI_PARSER_H

const char INI_READ_SUCCESS = 0;
const char INI_READ_COULDNT_OPEN = 1;
const char INI_READ_MALFORMED = 2;
const char INI_READ_NO_HEADERS = 3;
const char INI_READ_KEY_WITH_NO_HEADER = 4;

class INI_Parser {
public:
	/** Generic constructor */
	INI_Parser();
	
	/** Generic destructor */
	~INI_Parser();

	/** Read the specified file into memory, so its contents can be processed.
	 * Returns 0 on success and 1, 2, or 3 if something goes wrong (see
	 * INI_READ_* consts for specific errors)
	 * \return INI_READ_SUCCESS, INI_READ_NOT_FOUND, or INI_READ_NO_HEADERS,
	 */
	char ReadFile(std::string file);

	/** Check if the specified header exists.
	 * \param header The header to look for.
	 * \return true if the header exists, false if it doesn't.
	 */
	bool HeaderExists(std::string header);

	/** Check if the specified key exists in the specified header. Will throw
	 * HeaderNotFoundException if the header doesn't exist.
	 * \param header The header to look in.
	 * \param key The name of the key to look for.
	 * \return true if the header exists, false if it doesn't.
	 */
	bool KeyExists(std::string header, std::string key);

	/** Get the value of a particular key from a particular header, as an
	 * std::string. Will throw HeaderNotFoundException if the header doesn't
	 * exist, and KeyNotFoundException if the key doesn't.
	 * \param header The header to look in.
	 * \param key The name of the key whose value to get.
	 * \return The key's value, as an std::string.
	 */
	std::string GetKeyValue(std::string header, std::string key);

	/** Clears the file contents from memory. To access it again, the file must
	 * be re-read with ReadFile().
	 */
	void Unload();

private:
	// Each key represents a header: its value is another map, whose keys are
	// the keys for that header.
	std::map<std::string, std::map<std::string, std::string> > keymap;
};

// Header not found
class HeaderNotFoundException {
public:
	HeaderNotFoundException(std::string name) {
		_name = name;
	}

	~HeaderNotFoundException() {
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
	KeyNotFoundException(std::string header, std::string name) {
		_header = header;
		_name = name;
	}

	~KeyNotFoundException() {
		_header = "";
		_name = "";
	}

	std::string GetHeaderName() {
		return _header;
	}

	std::string GetName() {
		return _name;
	}

private:
	std::string _header;
	std::string _name;
};
#endif
// EOF
