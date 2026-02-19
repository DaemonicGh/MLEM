
#pragma once

#include <stddef.h>
#include <stdbool.h>

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

typedef struct mlem_value	mlem_value;
typedef struct mlem_pair	mlem_pair;

struct mlem_value {
	mlem_value_type	type;
	union {
		long		_int, _long;
		double		_float, _double;
		char*		_string;
		bool		_bool;
		mlem_value*	_array;
		mlem_pair*	_object;
	};
};

struct mlem_pair {
	char*		key;
	mlem_value	value;
};

char	*open_and_read_file(const char *filename);
