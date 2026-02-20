
#include <stdio.h>
#include <stdlib.h>

#include "mlem.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}

	char *str;

	str = open_and_read_file(argv[1]);
	mlem_tokenize(str);
	free(str);

	return (0);
}
