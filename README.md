# INI_Parser
Simple C++ class for parsing INI files

I wrote this because I was bored. It's possible I had no idea what I was doing. This hasn't had much testing.

If Wikipedia is correct about the format of these files (I didn't check it until
 after I wrote this, because I'm lazy), this has a few somewhat serious issues that I'll
 fix eventually.

It's for reading files structured like this:

```
# Lines starting with # are comments
[Section0]
key0=value0
key1=value1
key2=value2
# ...

[Section1]
key0=value0
key1=value1
# ...
```

You use it like this:

```
#include "INI_Parser.h"

...

INI_Parser ip;
ip.ReadFile("file.ini");
try {
	value1 = ip.GetKeyValue("Section", "Key1");
	value2 = ip.GetKeyValue("Section", "Key1");
	...
} catch (SectionNotFoundException h) {
	std::cout << "Section " << h.GetName() << " wasn't found" << std::endl;
} catch (KeyNotFoundException k) {
	std::cout << "Key " << k.GetSectionName() << "/" << k.GetName() <<
		" wasn't found" << std::endl;
}
ip.Unload()
```
 
You can also check whether a section or key exists with `SectionExists(Section)` or
`KeyExists(Section, key)`. It reads the whole file into memory all at once, so you
shouldn't use it for big files.
