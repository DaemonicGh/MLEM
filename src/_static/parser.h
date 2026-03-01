
#pragma once

#include "mlem.h"
#include "tokens.h"

mlem_value
parse_array(mlem_context *mlem, mlem_token *trigger_token);

mlem_value
parse_object(mlem_context *mlem, mlem_token *trigger_token);

mlem_value
parse_structure(mlem_context *mlem, mlem_token *trigger_token);

void
parse_start(mlem_context *mlem);

mlem_context
init_context(char *content, mlem_settings settings);

char*
open_and_read_file(const char *filename, mlem_error		*error);
