
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MLEM_NULL_VALUE (mlem_value){0}
#define MLEM_NULL_PAIR	(mlem_pair) {0}

typedef enum {
	TYPE_NULL = 0,
    TYPE_INT,
    TYPE_LONG = TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE = TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_ARRAY,
    TYPE_OBJECT
}	mlem_value_type;

typedef struct mlem_value_s	mlem_value;
typedef struct mlem_pair_s	mlem_pair;

typedef struct mlem_value_s {
	mlem_value_type	type;
	union {
		int64_t		_int, _long;
		double		_float, _double;
		char*		_string;
		bool		_bool;
		mlem_value	*_array;
		mlem_pair	*_object;
	};
}	mlem_value;

typedef struct mlem_pair_s {
	char*		key;
	mlem_value	value;
}	mlem_pair;

typedef struct {
	bool	nothing;
}	mlem_parser_settings;

// Functions

mlem_value	mlem_parse(char *content, mlem_parser_settings settings);
mlem_value	mlem_parse_file(const char *filename, mlem_parser_settings settings);
