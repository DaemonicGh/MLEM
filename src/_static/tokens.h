
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "context.h"

#define MLEM_NULL_TOKEN	(mlem_token){0}

typedef enum
{
	TK_NULL,

	TK_WORD				= 1 << 0,

	TK_OPEN_UNKNOWN		= 1 << 1,
	TK_CLOSE_UNKNOWN	= 1 << 2,
	TK_OPEN_ARRAY		= 1 << 3,
	TK_CLOSE_ARRAY		= 1 << 4,
	TK_OPEN_OBJECT		= 1 << 5,
	TK_CLOSE_OBJECT		= 1 << 6,

	TK_ASSIGN			= 1 << 7,

	TK_WORD_DEL			= 1 << 8,
	TK_ML_WORD_DEL		= 1 << 9,

	TK_COMMENT			= 1 << 10,
	TK_ML_COMMENT_DEL	= 1 << 11,
	TK_ML_COMMENT_START	= 1 << 12,
	TK_ML_COMMENT_END	= 1 << 13,

}	mlem_token_type;

typedef enum
{
	TKG_OPEN			= TK_OPEN_UNKNOWN | TK_OPEN_ARRAY | TK_OPEN_OBJECT,
	TKG_CLOSE			= TK_CLOSE_UNKNOWN | TK_CLOSE_ARRAY | TK_CLOSE_OBJECT,
	TKG_ML_COMMENT		= TK_ML_COMMENT_DEL | TK_ML_COMMENT_START | TK_ML_COMMENT_END,
	TKG_COMMENT			= TK_COMMENT | TKG_ML_COMMENT,

	TKG_VALUE			= TK_WORD | TKG_OPEN | TKG_CLOSE,
	TKG_SIGNIFICANT		= TKG_VALUE | TK_ASSIGN,

	TKG_ML				= TK_ML_WORD_DEL | TKG_ML_COMMENT,
	TKG_WORD_CONTENT	= TK_WORD_DEL | TK_ML_WORD_DEL,
	TKG_EXTENDS			= TKG_WORD_CONTENT | TKG_COMMENT,
}	mlem_token_type_group;

typedef struct {
	const mlem_token_type	type;
	const char				*start;
	const char				*end;
	const char				*error;
}	mlem_token_trigger;

typedef struct {
	mlem_token_type				type;
	const mlem_token_trigger	*trigger;
	char						*val;
	size_t						len;
}	mlem_token;

static const mlem_token_trigger token_triggers[] =
{
	{.type	= TK_ML_WORD_DEL,		.start = "'''",		.end = "'''"},
	{.type	= TK_ML_COMMENT_DEL,	.start = "///",		.end = "///"},
	{.type	= TK_ML_WORD_DEL,		.start = "\"\"\"",	.end = "\"\"\""},

	{.type	= TK_COMMENT,			.start = "//",		.end = "\n //"},
	{.type	= TK_ML_COMMENT_START,	.start = "/*",		.end = "*/"},
	{.type	= TK_ML_COMMENT_END,	.start = "*/"},

	{.type	= TK_OPEN_UNKNOWN,		.start = "["},
	{.type	= TK_CLOSE_UNKNOWN,		.start = "]"},
	{.type	= TK_ASSIGN,			.start = "="},
	{.type	= TK_WORD_DEL,			.start = "'",		.end = "' !",
	 .error	= "\n"},
	{.type	= TK_ML_WORD_DEL,		.start = "\"",		.end = "\""},
	{.type	= TK_OPEN_OBJECT,		.start = "{"},
	{.type	= TK_CLOSE_OBJECT,		.start = "}"},
	{.type	= TK_ASSIGN,			.start = ":"},
	{0}
};

static const char	*skip_triggers[] = {
	" ", "\t", "\n", ",", NULL
};

static const char	*token_repr[] = {
	"N", "W", "[", "]", "(", ")", "{", "}", "=",
	"'", "\"", "//", "///", "/*", "*/", NULL
};

void
print_token(mlem_token_type token);

bool
move_forward(mlem_context *mlem, size_t amount);

bool
move_past_blank(mlem_context *mlem);

bool
move_past_word(mlem_context *mlem);

size_t
move_past_token(mlem_context *mlem, mlem_token *token);

const mlem_token_trigger
*get_trigger(const char *s);

mlem_token
get_next_token(mlem_context *mlem);
