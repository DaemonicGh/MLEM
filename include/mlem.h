
#pragma once

#include <stddef.h>
#include <stdbool.h>

#define MLEM_NULL_VALUE (mlem_value){0}
#define MLEM_NULL_PAIR	(mlem_pair) {0}

typedef enum {
	TYPE_NULL = 0,
    TYPE_INT,
    TYPE_FLOAT,
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
		long		val_int;
		double		val_float;
		char		*val_string;
		bool		val_bool;
		mlem_value	*val_array;
		mlem_pair	*val_object;
	};
}	mlem_value;

typedef struct mlem_pair_s {
	char			*key;
	mlem_value		value;
}	mlem_pair;

typedef struct {
	bool			nothing;
}	mlem_settings;

// Functions

mlem_value
mlem_parse(
	char 			*content,
	mlem_settings	settings
);

mlem_value
mlem_parse_file(
	const char		*filename,
	char			**content,
	mlem_settings	settings
);

void
mlem_print_value(
	mlem_value		*val
);

void
mlem_destroy_value(
	mlem_value		*val,
	bool			free_strings
);
