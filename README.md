![MLEM logo](.github/assets/title_large.png)

\
*JSON was boring so I made this*\
&nbsp;

---

**MLEM** is a human-oriented data format designed for readable and moddable configuration files and data.\
\
**This project was made for fun and is still in development. Expect bugs, changes and incomplete features. Please report any misbehavior**

---

#### Why not JSON or YAML ?

**MLEM** aims to provide a middle ground between **JSON** and **YAML**,
less syntax-heavy than **JSON**, more predictable than **YAML**,
and offers an alternative designed for human-written data.\
\
The parser is currently only available in **C**, a port to **C++** might happen in the future.\
\
Any feedback or contributions are welcome!

---

## Goals

**MLEM** is designed for:

- Configuration files
- Game/modding data
- Human-edited data structures
- Lightweight C projects\
&nbsp;

---

## Features

- Minimal and readable syntax
- **JSON**-like data model, able to parse **JSON** and **JSON5** files
- A fast single-pass parser written in **C**
- A small API to manipulate the data **MLEM** parses
- A serializer that tries its best to keep your values as they were originally

### Syntax

- Newlines, indentation, commas and spacing **don't matter**.
- Most values are **case-insensitive**.
- **Strings do not require quotes** unless they contain spaces or special characters.
- Square brackets `[]` can be used for both **arrays and objects**.
**MLEM** will automatically determine the intended structure.
- Equals `=` are used to determine **key-value pairs**.
- Comments starts with `//`, or `///` on both ends for multiline comments.

### Types

Of course, **MLEM** supports all the standard **JSON** types, plus some extras.

| Type | C value | Example
|------|---------|--------
| **Integer** | int64_t | `1, -3, 0xFFAA85, 3625304601213135`
| **Float** | double | `3.14, -.6, 1.87e-3`
| **String** | char* | `"Hello!" Not_even_quoted 'Spaced text\n'`
| **Boolean** | bool | `True, False`
| **Array** | t_mlem_value[]| `["MLEM" wow 147]`
| **Object** | t_mlem_pair[]| `[key = value enabled = true] {other : format}`
| **Constant** | varies | `NaN, Inf, Null`
| **Reference** | t_mlem_reference*| `#reference`
| **Template** (WIP) | t_mlem_template*| `<required INT[0 1] [ON OFF] = 1>`

\
More information about types and syntax can be found on the [wiki](https://github.com/DaemonicGh/MLEM/wiki).

---

## Example

Here's what **MLEM** looks like:

```
// World settings
world = [
	name = MyWorld
	seed = 12345
	hard_mode = true
	playtime = 1.56
	
	spawn_point = [
		x = 128
		y = 64
	]
	players = [JohnZ lily123 _Horse]
]
```

---

## Usage

First of all, clone the repository and build it.

```bash
git clone git@github.com:DaemonicGh/MLEM.git MLEM
make -C MLEM
```

You can then include the header `MLEM/include/mlem.h` in your project.\
\
Here's a simple example:

```c
#include <stdio.h>
#include "mlem.h"

int	main(void) {
	t_mlem_value	constants;
	t_mlem_value	value;

	constants = mlem_parse("constants.mlem", NULL, (t_mlem_value){0});
	value = mlem_parse("example.mlem", NULL, constants);
	printf("Parsed value:\n");
	mlem_print(stdout, value);
	if (value.type)
	{
		// Assuming the mlem file is properly formatted
		t_mlem_value	cat = mlem_object_get(value, "cat");
		printf("The cat's name is %s\n", mlem_object_get(cat, "name").string_v);
	}
	mlem_destroy(value);
	mlem_destroy(constants);
	return (0);
}
```

More information about the internals and API can be found on the [wiki](https://github.com/DaemonicGh/MLEM/wiki).
