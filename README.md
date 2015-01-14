# INI_Parser
Simple C++ class for parsing INI files

I wrote this because I was bored. It's possible I had no idea what I was doing. This hasn't had much testing.

It's for reading files structured like this:

```
# Lines starting with # are comments
[Header0]
key0=value0
key1=value1
key2=value2
# ...

[Header1]
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
	value1 = ip.GetKeyValue("Header", "Key1");
	value2 = ip.GetKeyValue("Header", "Key1");
	...
} catch (HeaderNotFoundException h) {
	std::cout << "Header " << h.GetName() << " wasn't found" << std::endl;
} catch (KeyNotFoundException k) {
	std::cout << "Key " << k.GetHeaderName() << "/" << k.GetName() <<
		" wasn't found" << std::endl;
}
ip.Unload()
```
 
You can also check whether a header or key exists with `HeaderExists(header)` or
`KeyExists(header, key)`. It reads the whole file into memory all at once, so you
shouldn't use it for big files.
