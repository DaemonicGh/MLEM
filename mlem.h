
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

typedef struct mlem_value_s	mlem_value;
typedef struct mlem_pair_s	mlem_pair;

struct mlem_value_s {
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

struct mlem_pair_s {
	char*		key;
	mlem_value	value;
};

// temp

typedef enum {
	TK_NULL,

	// First Stage only
	TK_WORD,
	TK_OPEN_UNKNOWN,
	TK_CLOSE_UNKNOWN,
	TK_WORD_DEL,
	TK_ML_WORD_DEL,
	TK_COMMENT,
	TK_ML_COMMENT_DEL,
	TK_ML_COMMENT_START,
	TK_ML_COMMENT_END,

	TK_KEY,
	TK_VALUE,
	TK_ASSIGN,
	TK_OPEN_ARRAY,
	TK_CLOSE_ARRAY,
	TK_OPEN_OBJECT,
	TK_CLOSE_OBJECT,
}	TokenType;

typedef struct {
	TokenType		type;
	size_t			line;
	size_t			column;
	const char*		val;
	const char*		trigger;
}	Token;

Token*	mlem_tokenize(const char* content);

//

#define MLEM_NULL_VALUE (mlem_value){0}

mlem_value	mlem_parse(const char *content);
mlem_value	mlem_parse_file(const char *filename);

char*	open_and_read_file(const char *filename);
