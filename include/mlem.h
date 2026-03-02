
#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {
	ERR_NONE,

	ERR_UNEXPECTED_ERROR,

	ERR_FILE,
	ERR_MEMORY,

	ERR_NULL_INPUT,
	ERR_UNEXPECTED_TOKEN,
	ERR_UNCLOSED_SYMBOL,
	ERR_UNCLOSED_STRUCTURE,
	ERR_WRONG_STRUCTURE_CLOSE,
	ERR_ASSIGN_IN_ARRAY,
	ERR_EXPECTED_ASSIGN,
	ERR_EXPECTED_VALUE,

	ERR_INVALID_NUMBER,
	ERR_NUMBER_OUT_OF_RANGE,
	ERR_INVALID_BASE_PREFIX,
	ERR_EMPTY_EXPONENT,
	ERR_INVALID_EXPONENT

}	mlem_error;

typedef enum {
	MLEM_TYPE_ERROR,
	MLEM_TYPE_NULL,
    MLEM_TYPE_INT,
    MLEM_TYPE_FLOAT,
    MLEM_TYPE_STRING,
    MLEM_TYPE_BOOL,
    MLEM_TYPE_ARRAY,
    MLEM_TYPE_OBJECT
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

#define MLEM_VALUE(t)		(mlem_value){.type = (t)}

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
