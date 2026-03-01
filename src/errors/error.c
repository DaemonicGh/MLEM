
#include <stdio.h>

#include "errors.h"
#include "mlem.h"
#include "tokens.h"

mlem_error
set_error(mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s\x1B[0m\n", error_messages[type]);
	return (type);
}

mlem_error
set_error_l(mlem_context *mlem, mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s at line %zi:%zi\x1B[0m\n",
		error_messages[type], mlem->line, mlem->column);
	mlem->error = type;
	return (type);
}

mlem_error
set_error_t(mlem_context *mlem, mlem_token *token, mlem_error type)
{
	fprintf(stderr, "\x1B[1;31mMLEM: %s at line %zi:%zi > %.*s\x1B[0m\n",
		error_messages[type], mlem->line, mlem->column,
		(int)token->len, token->val);
	mlem->error = type;
	return (type);
}