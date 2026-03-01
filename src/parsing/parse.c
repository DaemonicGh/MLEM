
#include <stdio.h>
#include <strings.h>

#include "mlem.h"
#include "errors.h"
#include "parser.h"

mlem_value
mlem_parse(char *content, mlem_settings settings)
{
	mlem_token			start_token = {.type = TK_OPEN_UNKNOWN, .trigger = &token_triggers[6]};
	mlem_context		mlem;
	mlem_value			structure;

	if (!content)
	{
		set_error(ERR_NULL_INPUT);
		return (MLEM_ERROR_VALUE(ERR_NONE));
	}
	mlem = init_context(content, settings);
	parse_start(&mlem);
	printf("Starting parsing\n");
	structure = parse_structure(&mlem, &start_token);
	if (!structure.type)
		return (MLEM_ERROR_VALUE(mlem.error));
	return (structure);
}

mlem_value
mlem_parse_file(const char *filename, char **content, mlem_settings settings)
{
	mlem_error error;

	*content = open_and_read_file(filename, &error);
	if (!*content)
		return (MLEM_ERROR_VALUE(error));
	printf("Read File\n");
	return (mlem_parse(*content, settings));
}
