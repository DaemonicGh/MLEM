/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:23:28 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:33:44 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

const struct s_mlem_data			g_mlem_data = {
	.tokens = {
{0}, {
	.type = TKN_UNEXPECTED
}, {
	.type = TKN_UNEXPECTED,
	.value = "*/", .len = 2
}, {
	.type = TKN_SKIP,
	.whitelist = TKN_SKIP
}, {// Newline
	.type = TKN_SKIP,
	.whitelist = TKN_SKIP
}, {
	.type = TKN_BACKSLASH, .len = 2,
	.data = MLEM_STR_UNQUOTED,
	.whitelist = TKN_WORD | TKN_NUMBER | TKN_CONTINUE | TKN_BACKSLASH
}, {
	.type = TKN_EOF
}, {
	.type = TKN_CONTINUE
}, {
	.type = TKN_COMMENT,
	.value = "//", .len = 2,
	.trg_blacklist = {TRG_SS_COMMENT, TRG_NEWLINE}
}, {
	.type = TKN_COMMENT,
	.value = "///", .len = 3,
	.trg_blacklist = {TRG_SSS_COMMENT}
}, {
	.type = TKN_COMMENT,
	.value = "/*", .len = 2,
	.trg_blacklist = {TRG_ST_COMMENT_END}
}, {
	.type = TKN_WORD,
	.data = MLEM_STR_UNQUOTED,
	.whitelist = TKN_WORD | TKN_NUMBER | TKN_CONTINUE | TKN_BACKSLASH
}, {
	.type = TKN_NUMBER,
	.whitelist = TKN_WORD | TKN_NUMBER | TKN_BACKSLASH
}, {
	.type = TKN_STRING, .len = 1,
	.data = MLEM_STR_QUOTED,
	.trg_blacklist = {TRG_Q_STRING},
	.trg_errorlist = {TRG_NEWLINE},
}, {
	.type = TKN_STRING, .len = 1,
	.data = MLEM_STR_DQUOTED,
	.trg_blacklist = {TRG_DQ_STRING}
}, {
	.type = TKN_STRING,
	.value = "'''", .len = 3,
	.data = MLEM_STR_3QUOTED,
	.trg_blacklist = {TRG_3Q_STRING}
}, {
	.type = TKN_STRING,
	.value = "\"\"\"", .len = 3,
	.data = MLEM_STR_3DQUOTED,
	.trg_blacklist = {TRG_3DQ_STRING}
}, {
	.type = TKN_REFERENCE, .len = 1,
	.data = MLEM_STR_UNQUOTED,
	.whitelist = TKN_WORD | TKN_NUMBER | TKN_CONTINUE | TKN_BACKSLASH
}, {
	.type = TKN_ASSIGN, .len = 1,
}, {
	.type = TKN_OPEN, .len = 1,
	.data = TRGDATA_STRUCTURE
}, {
	.type = TKN_OPEN,
	.value = "|[", .len = 2,
	.data = TRGDATA_ARRAY
}, {
	.type = TKN_OPEN,
	.value = "[*", .len = 2,
	.data = TRGDATA_PACKED_ARRAY
}, {
	.type = TKN_OPEN,
	.value = "|[*", .len = 3,
	.data = TRGDATA_PACKED_ARRAY
}, {
	.type = TKN_OPEN, .len = 1,
	.data = TRGDATA_OBJECT
}, {
	.type = TKN_OPEN, .len = 1,
	.data = TRGDATA_TEMPLATE
}, {
	.type = TKN_CLOSE, .len = 1,
	.data = TRGDATA_STRUCTURE | TRGDATA_ARRAY | TRGDATA_PACKED_ARRAY
}, {
	.type = TKN_CLOSE,
	.value = "]|", .len = 2,
	.data = TRGDATA_ARRAY | TRGDATA_PACKED_ARRAY
}, {
	.type = TKN_CLOSE, .len = 1,
	.data = TRGDATA_OBJECT
}, {
	.type = TKN_CLOSE, .len = 1,
	.data = TRGDATA_TEMPLATE
}
}, .char_data.tokens = {
{TRG_EOF},														// \0
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x01-\x03
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x04-\x06
{TRG_UNEXPECTED}, {TRG_UNEXPECTED},								// \x07-\x08
{TRG_SKIP},														// \t
{TRG_NEWLINE},													// \n
{TRG_SKIP}, {TRG_SKIP}, {TRG_SKIP},								// \v \f \r
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x0E-\x10
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x11-\x13
{TRG_UNEXPECTED}, {TRG_UNEXPECTED},	{TRG_UNEXPECTED},			// \x14-\x16
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x17-\x19
{TRG_UNEXPECTED},												// \x1A
{TRG_WORD},														// ESC
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// \x1C-\x1E
{TRG_UNEXPECTED},												// \x1F
{TRG_SKIP},														// SPACE
{TRG_UNEXPECTED},												// !
{TRG_3DQ_STRING, TRG_DQ_STRING},								// "
{TRG_REFERENCE},												// #
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// $ % &
{TRG_3Q_STRING, TRG_Q_STRING},									// '
{TRG_UNEXPECTED}, {TRG_UNEXPECTED}, {TRG_UNEXPECTED},			// ( ) *
{TRG_NUMBER},													// +
{TRG_SKIP},														// ,
{TRG_NUMBER}, {TRG_NUMBER},										// - .
{TRG_SSS_COMMENT, TRG_SS_COMMENT, TRG_ST_COMMENT_START},		// /
{TRG_NUMBER}, {TRG_NUMBER}, {TRG_NUMBER}, {TRG_NUMBER},			// 0-3
{TRG_NUMBER}, {TRG_NUMBER},	{TRG_NUMBER}, {TRG_NUMBER},			// 4-7
{TRG_NUMBER}, {TRG_NUMBER},										// 8-9
{TRG_ASSIGN},													// :
{TRG_UNEXPECTED},												// ;
{TRG_OPEN_TEMPLATE},											// <
{TRG_ASSIGN},													// =
{TRG_CLOSE_TEMPLATE},											// >
{TRG_UNEXPECTED},												// ?
{TRG_UNEXPECTED},												// @
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// A-E
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// F-J
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// K-O
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// P-T
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// U-Y
{TRG_WORD},														// Z
{TRG_OPEN_PACKED_ARRAY, TRG_OPEN_STRUCTURE},					// [
{TRG_BACKSLASH},												// BACKSLASH
{TRG_CLOSE_ARRAY, TRG_CLOSE_STRUCTURE},							// ]
{TRG_UNEXPECTED},												// ^
{TRG_WORD},														// _
{TRG_UNEXPECTED},												// `
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// a-e
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// f-j
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// k-o
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// p-t
{TRG_WORD},	{TRG_WORD}, {TRG_WORD}, {TRG_WORD}, {TRG_WORD},		// u-y
{TRG_WORD},														// z
{TRG_OPEN_OBJECT},												// {
{TRG_P_OPEN_PACKED_ARRAY, TRG_OPEN_ARRAY, TRG_UNEXPECTED},		// |
{TRG_CLOSE_OBJECT},												// }
{TRG_UNEXPECTED}, {TRG_UNEXPECTED},								// ~ DEL
}, .constants = {
{0}, {
{.name = "Inf",		.value = {
	.floatv = {.type = MLEM_TYPE_FLOAT,	.value = INFINITY}}},
{.name = "INT_MIN",	.value = {
	.intv = {.type = MLEM_TYPE_INT, .value = INT64_MIN}}},
{.name = "INT_MAX",	.value = {.intv = {
	.type = MLEM_TYPE_INT, .value = INT64_MAX}}}
}, {
{.name = "Null",	.value = {.type = MLEM_TYPE_NULL}},
{.name = "NaN",		.value = {.floatv = {
	.type = MLEM_TYPE_FLOAT, .value = NAN}}},
}, {
{.name = "False",	.value = {.boolv = {
	.type = MLEM_TYPE_BOOL,	.value = false}}}
}, {
{.name = "True",	.value = {.boolv = {
	.type = MLEM_TYPE_BOOL,	.value = true}}}
}, {
{.name = "-Inf",	.value = {.floatv = {
	.type = MLEM_TYPE_FLOAT,	.value = -INFINITY}}}
}
}, /*
	\0  SOH STX ETX EOT ENQ ACK \a  \b  \t  \n  \v  \f  \r  SO  SI
	DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM SUB ESC  FS  GS  RS  US
		!   "   #   $   %   &   '   (   )   *   +   ,   -   .   /
	0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?
	@   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O
	P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _
	`   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o
	p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~   DEL
	*/
	.char_data.constants = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	3,	0,	0,	1,	0,	0,	0,	0,	2,	0,
	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	3,	0,	0,	1,	0,	0,	0,	0,	2,	0,
	0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	.char_data.transform = ""
	" "	" "	" "	" "	" "	" "	" "	" "	" "	"\t""\n""\v""\f""\r"" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	"\""" "	" "	" "	" " "'"	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	"\\"" "	" "	" "
	" "	"\a""\b"" "	" "	"\e""\f"" "	" "	" "	" "	" "	" "	" "	"\n"" "
	" "	" "	"\r"" "	"\t"" "	"\v"" "	" "	" "	" "	" "	" "	" "	" "	" ",
	.char_data.number = {
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,	20,	21,	22,	23,	24,
	25,	26,	27,	28,	29,	30,	31,	32,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,	20,	21,	22,	23,	24,
	25,	26,	27,	28,	29,	30,	31,	32,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1},
	.char_data.base = {
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	2,	-1,	12,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	8,
	-1,	4,	-1,	-1,	-1,	1,	-1,	-1,	16,	-1,	32,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	2,	-1,	12,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	8,
	-1,	4,	-1,	-1,	-1,	1,	-1,	-1,	16,	-1,	32,	-1,	-1,	-1,	-1,	-1},
	.repr_data = {
	.transform = ""
	"0"	"x"	"x"	"x"	"x"	"x"	"x"	"a"	"b"	"t"	"n"	"v"	"f"	"r"	"x"	"x"
	"x"	"x"	"x"	"x"	"x"	"x"	"x"	"x"	"x"	"x"	"x"	"e"	"x"	"x"	"x"	"x"
	" "	" "	" "	" "	" "	" "	" " " "	" "	" "	" "	" "	" "	" "	" "	" "
	" " " "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	"\\"" "	" " " "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "
	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" "	" ",
	.number = "0123456789ABCDEFGHIJKLMNOPQRSTUV",
	.base = " ubtq   o   d   x               z",
	.flavor = {
	"", "", "'", "\\?", "\"", "\\?", "\\?", "\\?", "'''",
	"\\?", "\\?", "\\?", "\\?", "\\?", "\\?", "\\?", "\"\"\""}
}
};

const t_mlem_template_flag_def		g_template_flags[] = {
{
	.type = MLEM_TPF_REQUIRED,
	.values = {"required", "!", "req"}
}, {
	.type = MLEM_TPF_CLAMP,
	.values = {"clamp", "%", "?c"},
	.blacklist = MLEM_TPF_STRICT_BOUNDS
}, {
	.type = MLEM_TPF_CONVERT,
	.values = {"convert", "?", "conv"}
}, {
	.type = MLEM_TPF_FLATTEN,
	.values = {"flatten", "?f"}
}, {
	.type = MLEM_TPF_STRICT_TYPE
	| MLEM_TPF_STRICT_BOUNDS
	| MLEM_TPF_NO_WILDCARD,
	.values = {"strict", "~"},
	.blacklist = MLEM_TPF_CLAMP | MLEM_TPF_CONVERT
}, {
	.type = MLEM_TPF_STRICT_TYPE,
	.values = {"strict_type", "~t"},
	.blacklist = MLEM_TPF_CONVERT
}, {
	.type = MLEM_TPF_STRICT_BOUNDS,
	.values = {"strict_bounds", "~b"},
	.blacklist = MLEM_TPF_CLAMP
}, {
	.type = MLEM_TPF_NO_WILDCARD,
	.values = {"no_wildcard", "~*"}
}, {0}
};

const t_mlem_subtemplate_trigger	g_template_structures[] = {
{
	.triggers = {"ARRAY", "A"},
	.type = MLEM_TYPE_ARRAY
}, {
	.triggers = {"OBJECT", "OBJ", "O"},
	.type = MLEM_TYPE_OBJECT
}, {0}
};

const t_mlem_subtemplate_trigger	g_subtemplates[] = {
{
	.triggers = {"INT", "I"},
	.type = MLEM_TYPE_INT
}, {
	.triggers = {"FLOAT", "F"},
	.type = MLEM_TYPE_FLOAT
}, {
	.triggers = {"BOOL", "B"},
	.type = MLEM_TYPE_BOOL
}, {
	.triggers = {"STRING", "STR", "S"},
	.type = MLEM_TYPE_STRING
}, {
	.triggers = {"TEMPLATE", "T"},
	.type = MLEM_TYPE_TEMPLATE
}, {
	.triggers = {"UINT", "U"},
	.type = MLEM_TYPE_INT, .range = {0, INT64_MAX},
}, {
	.triggers = {"INT64", "I64"},
	.type = MLEM_TYPE_INT, .range = {INT64_MIN, INT64_MAX}
}, {
	.triggers = {"UINT64", "U64"},
	.type = MLEM_TYPE_INT, .range = {0, INT64_MAX}
}, {
	.triggers = {"INT32", "I32"},
	.type = MLEM_TYPE_INT, .range = {INT32_MIN, INT32_MAX}
}, {
	.triggers = {"UINT32", "U32"},
	.type = MLEM_TYPE_INT, .range = {0, UINT32_MAX}
}, {
	.triggers = {"INT8", "I8"},
	.type = MLEM_TYPE_INT, .range = {INT8_MIN, INT8_MAX}
}, {
	.triggers = {"UINT8", "U8"},
	.type = MLEM_TYPE_INT, .range = {0, UINT8_MAX}
}, {
	.triggers = {"INT16", "I16"},
	.type = MLEM_TYPE_INT, .range = {INT16_MIN, INT16_MAX}
}, {
	.triggers = {"UINT16", "U16"},
	.type = MLEM_TYPE_INT, .range = {0, UINT16_MAX}
}, {0}
};

// ERRORS

const char							*g_error_messages[][2] = {
{"Empty value", "This value was probably set by (t_mlem_value){0}"},
{"Unexpected error"},
{"Memory error"},
{"Unable to open file"},
{"File is empty"},
{"Reference table isn't an array"},
{"Unexpected token"},
{"Invalid backslash symbol"},
{"Unclosed symbol"},
{"Unclosed structure"},
{"Incorrect closing symbol"},
{"Unexpected closing symbol"},
{"Object assignment in array"},
{"Expected assignment symbol"},
{"Expected value"},
{"Invalid string",
	"Unquoted strings must start with an alpha character or an underscore"},
{"Invalid key", "Place it in quotations marks"},
{"Key already in object"},
{"Invalid number"},
{"Invalid number", "Add a 0"},
{"Invalid value base prefix", "Accepted prefixes are b,t,q,o,d,x and z"},
{"Invalid number", "Make sure all characters fits within the given base"},
{"Numeric value out of 64-bit range"},
{"Numeric value reached infinity", "Use INF and -INF to get infinity"},
{"Empty value exponent"},
{"Invalid value exponent"},
{"Packed array cannot be empty"},
{"Value cannot be contained in a packed array",
	"Packed arrays can only contain numbers, booleans, strings and references"},
{"Value type doesn't match packed array"},
{"Value type doesn't match packed array",
	"The first array value must be explictely set to a float"},
{"Undefined reference"},
{"Reference already exists locally",
	"A reference cannot be overriden"},
{"Reference refers to itself"},
{"Reference recursion limit reached", "The limit is 255"},
{"Template flag is already set"},
{"Template structure definiton is already present",
	"Place it in another template to have nested structures"},
{"Invalid template value"},
{"Template value reference isn't a template",
	"Put the referenced value in < >"},
{"Template value contains non-template elements"},
{"Match: No corresponding match"},
{"Match: Unaccepted wildcard"},
{"Match: Missing required value"},
{"Match: Unaccepted out of bounds value"},
{0}
};
