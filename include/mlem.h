
#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum e_mlem_error
{
	ERR_NONE,
	ERR_UNEXPECTED_ERROR,
	ERR_FILE,
	ERR_MEMORY,
	ERR_NULL_INPUT,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_BACKSLASH,
	ERR_UNCLOSED_SYMBOL,
	ERR_UNCLOSED_STRUCTURE,
	ERR_WRONG_STRUCTURE_CLOSE,
	ERR_ASSIGN_IN_ARRAY,
	ERR_EXPECTED_ASSIGN,
	ERR_EXPECTED_VALUE,
	ERR_DUPLICATED_KEY,
	ERR_INVALID_NUMBER,
	ERR_NUMBER_OUT_OF_RANGE,
	ERR_INVALID_BASE_PREFIX,
	ERR_EMPTY_EXPONENT,
	ERR_INVALID_EXPONENT
}	t_mlem_error;

typedef enum e_mlem_value_type
{
	MLEM_TYPE_ERROR,
	MLEM_TYPE_NULL,
    MLEM_TYPE_INT,
    MLEM_TYPE_FLOAT,
    MLEM_TYPE_STRING,
    MLEM_TYPE_BOOL,
    MLEM_TYPE_ARRAY,
    MLEM_TYPE_OBJECT
}	t_mlem_value_type;

typedef struct s_mlem_value_s	t_mlem_value;
typedef struct s_mlem_pair_s	t_mlem_pair;

typedef struct s_mlem_value_s
{
	t_mlem_value_type	type;
	union {
		long		val_int;
		double		val_float;
		char		*val_string;
		bool		val_bool;
		t_mlem_value	*val_array;
		t_mlem_pair	*val_object;
	};
}	t_mlem_value;

typedef struct s_mlem_pair_s
{
	char			*key;
	t_mlem_value		value;
}	t_mlem_pair;

typedef struct s_mlem_settings
{
	bool			nothing;
}	t_mlem_settings;

#define MLEM_VALUE(t)		(t_mlem_value){.type = (t)}

// Functions

t_mlem_value
mlem_parse(
	char 			*content,
	t_mlem_settings	settings
);

t_mlem_value
mlem_parse_file(
	const char		*filename,
	char			**content,
	t_mlem_settings	settings
);

void
mlem_print_value(
	t_mlem_value		*val
);

void
mlem_destroy_value(
	t_mlem_value		*val,
	bool			free_strings
);
