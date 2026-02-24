
#include <stdio.h>
#include <strings.h>

#include "mlem.h"
#include "parser.h"

mlem_value
mlem_parse(char *content, mlem_settings settings)
{
	mlem_token			start_token = {.type = TK_OPEN_UNKNOWN, .trigger = &token_triggers[6]};
	mlem_context		mlem;
	mlem_value			structure;

	mlem = init_context(content, settings);
	if (!mlem.content)
		return (MLEM_NULL_VALUE);
	parse_start(&mlem);
	printf("Starting parsing\n");
	structure = parse_structure(&mlem, &start_token);
	return (structure);
}

mlem_value
mlem_parse_file(const char *filename, char **content, mlem_settings settings)
{
	*content = open_and_read_file(filename);
	if (!*content)
		return (MLEM_NULL_VALUE);
	printf("Read File\n");
	return (mlem_parse(*content, settings));
}
