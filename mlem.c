
#include <stdlib.h>
#include <stdio.h>

#include "mlem.h"

// Private header

typedef enum {
	ERR_EMPTY,
	ERR_FILE,
	ERR_MEMORY,
}	errors;

// Globals

static const char*	error_messages[] = {
	"",
	"File error",
	"Memory error"
};

// Utils

static inline void	error(errors type)
{
	fprintf(stderr, "MLEM: %s\n", error_messages[type]);
}

char	*open_and_read_file(const char *filename)
{
	FILE	*file;
	char	*content;
	size_t	content_size;

	file = fopen(filename, "r");
	if (!file)
	{
		error(ERR_FILE);
		return (NULL);
	}

	fseek(file, 0, SEEK_END);
	content_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	content = malloc(content_size + 1);
	if (!content)
	{
		error(ERR_MEMORY);
		return (NULL);
	}

	fread(content, 1, content_size, file);
	content[content_size] = '\0';

	fclose(file);
	return (content);
}
