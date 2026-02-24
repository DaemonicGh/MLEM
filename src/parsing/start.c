
#include "parser.h"

void
parse_start(mlem_context *mlem)
{
	(void)mlem;
	return ;
}

mlem_context
init_context(char *content, mlem_settings settings)
{
	mlem_context	mlem = {
		.line = 1, .column = 1, .depth = -1,
		.content = content, .settings = settings
	};
	return (mlem);
}
