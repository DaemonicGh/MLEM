
#include <stdio.h>
#include "errors.h"

void
error(mlem_context *mlem, mlem_errors type)
{
	if (mlem)
		fprintf(stderr, "\x1B[1;31mMLEM: %s at line %zi:%zi\x1B[0m\n",
			error_messages[type], mlem->line, mlem->column);
	else
		fprintf(stderr, "\x1B[1;31mMLEM: %s\x1B[0m\n",
			error_messages[type]);
}
