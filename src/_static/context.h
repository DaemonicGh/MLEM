
#pragma once

#include "mlem.h"

typedef struct {
	char					*content;
	mlem_settings			settings;
	mlem_error				error;
	size_t					line;
	size_t					column;
	size_t					depth;
}	mlem_context;
