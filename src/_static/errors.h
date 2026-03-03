
#pragma once

#include "context.h"
#include "tokens.h"

static const char	*error_messages[] = {
	"",
	"Unexpected error",
	"Unable to open file",
	"Memory error",
	"Given string is null",
	"Unexpected token",
	"Invalid backslash symbol",
	"Unclosed symbol",
	"Unclosed structure",
	"Incorrect closing symbol",
	"Object assignment in array",
	"Expected assignment symbol",
	"Expected value",
	"Key already in object",
	"Invalid number",
	"Numeric value out of 64-bit range",
	"Invalid value base prefix",
	"Empty value exponent",
	"Invalid value exponent"
};

#define MLEM_ERROR_VALUE(err)	(mlem_value){.type = MLEM_TYPE_ERROR, .val_int = (err)}

mlem_error
set_error(mlem_error type);

mlem_error
set_error_l(mlem_context *mlem, mlem_error type);

mlem_error
set_error_t(mlem_context *mlem, mlem_token *token, mlem_error type);
