
#pragma once

#include "context.h"

typedef enum {
	ERR_EMPTY,

	ERR_UNEXPECTED_ERROR,

	ERR_FILE,
	ERR_MEMORY,

	ERR_UNEXPECTED_TOKEN,
	ERR_UNCLOSED_SYMBOL,

	ERR_UNCLOSED_STRUCTURE,
	ERR_WRONG_STRUCTURE_CLOSE,
	ERR_ASSIGN_IN_ARRAY,

}	mlem_errors;

static const char	*error_messages[] = {
	"",
	"Unexpected error",
	"Unable to open file",
	"Memory error",
	"Unexpected token",
	"Unclosed symbol",
	"Unclosed structure",
	"Incorrect closing symbol",
	"Object assignment in array"
};

void
error(mlem_context *mlem, mlem_errors type);
