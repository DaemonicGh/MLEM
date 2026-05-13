# MLEM Syntax Overview

---

# The file

To write and parse MLEM data, you of course need a file to store your data in.\
The file must be a plain text file. It is strongly recommended to use the `.mlem` extension.\

An example of a valid MLEM file would be `my_data.mlem`.

---

## File contents

The only thing you need to write in an MLEM file is the data you want to store.\
You don't need to create a main structure like in JSON, you can simply write your data as-is.\
\
For example, this will return an array containing the numbers `1`, `2`, and `3`:
```mlem
1
2
3
```

And this will return an object containing a single key `name` with the value `John`:
```mlem
name = John
```

As you can see, **MLEM automatically detects if the file contains an array or an object.**
More details on this later.

---

# Values

---

## Strings

MLEM has a few string formats to choose from. Here's a quick overview:

| String Format | Example | Multiline | Supports Escaping |
| --- | --- | --- | --- |
| Plain text | `Hello, World!` | No | Yes |
| Single quoted | `'Hello, World!'` | No | Yes |
| Double quoted | `"Hello, World!"` | Yes | Yes |
| Triple quoted  | `'''Hello, World!'''` or `"""Hello, World!"""` | Yes | No |

A value is considered a string if it is enclosed in its corresponding quotes.\
If a single quoted string encounters a newline before its closing quote, an error will be raised.

---

### Plain text strings

To be considered a plain text string, A value must start with an alphabetic character (`a`-`z` `A`-`Z`) or an underscore (`_`).
A plain text string ends as soon as it encounters a space character or a sequence that could be interpreted as another value,
such as quotes or brackets, with an exception for numbers and constant values.

Here are some examples of valid plain text strings in MLEM:
```mlem
Hello
hi!
_mlem
ABC123
Symbols+-*.
```

And here are some examples of strings that would not behave as expected:
```mlem
123starting_numbers
brackets[]{}
sensitive_symbols#=:
```

As a good practice, a string that contains symbols or spaces should be enclosed in quotes.

---

### Escaped strings

Strings that support escaping will transform escape sequences into their corresponding characters.\
MLEM currently supports C `\n \t \e ...` and hexadecimal `\x` escape sequences.\
\
Backslashes can also be used in unquoted strings to force a character in.\
\
In quoted strings, an unrecognized escape sequence will raise an error.

```mlem
Unquoted\=Equal
Spaced\ unquoted\ string
\#unquoted

"Hello,\nWorld!"
'Backslash: \\'

'''
This won't become a newline -> \n
because it's in a triple quoted string
'''
```

---

## Numbers

In MLEM, numbers are either integers or floats.

A value is considered a number if it starts with a digit, a decimal point or a sign (`+`/`-`).\
A number that doesn't contain any digits will raise an error.\
From there, multiple factors will determine if the number is an integer or a float. 
- A base descriptor `0x 0b ...` will interpret the number as an integer.
- A decimal point `.` or an exponent `e` will interpret the number as a float.

---

### Integers

Integers are represented the same way most languages do:
a sequence of digits with an optional `+` or `-` sign in front.
MLEM will also accept and skip any underscores (`_`) in the number.

```mlem
42
-10
+75_413_241_012
```

MLEM stores integers as a 64-bit signed integer.\
An integer can therefore represent values from `-9223372036854775808` to `9223372036854775807`.\
A value that exceeds this range will raise an error.

As mentioned above, integers support non base-10 numbers.\
Such values start with a `0` followed by a character defining the base.\
Characters representing values over 10 use the standard `a`-`z` range. They are case-insensitive.
\
MLEM supports the following base descriptors:

| Base | Descriptor | Example |
| --- | --- | --- |
| 2 | `0b` | `0b1010` |
| 3 | `0t` | `-0t1221` |
| 4 | `0q` | `0q3201` |
| 8 | `0o` | `0o75_124` |
| 12 | `0d` | `+0d1A79B` |
| 16 | `0x` | `-0xaf73` |
| 32 | `0z` | `0zGL8N` |

---

### Floats

Floats are numbers with either a decimal part or an exponent.

Floats follows the same basic rules as integers,\
They allow a starting `+` or `-` sign and underscore characters (`_`) to separate digits.\
However, floats only support base-10 numbers.

MLEM stores floats as a 64-bit floating-point number.\
MLEM will try to detect values that loose precision and raise an error.\
This detection only applies to the number before any exponent is applied.\
Note that it isn't perfect and may not catch small losses.

Floats can start or end with a decimal point `.` without any digits before or after.

Floats support scientific notation using `e`(case-insensitive) as the exponent separator.\
Floats with an exponent will be multiplied by `10` raised to the power of the exponent value,\
with negative exponents performing a division rather than a multiplication.\
The exponent value must be a base-10 integer.
Floats with an exponent do not require a decimal point.

```mlem
.129
18.
3.14e2
187e-8
```

---

## Wiki under construction, sorry for the inconvenience.

## Arrays

...

---

## Objects

...

---

## Booleans, null and constants
...

---

## References

...

---

## Templates

...

---

# Non-value elements

---

## Comments

...
