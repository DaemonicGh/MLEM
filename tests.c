
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mlem.h"

void	print_array(mlem_value *val, int depth)
{
	mlem_value	v;
	char		tab[128] = "                                                                                                                                ";
	tab[depth << 1] = 0;

	printf("%s[\n", tab);
	for (size_t i = 0; val->_array[i].type; i++)
	{
		v = val->_array[i];
		if (v.type == TYPE_ARRAY)
			print_array(&v, depth + 1);
		else
			printf("  %s\"%s\"\n", tab, v._string);
	}
	printf("%s]\n", tab);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}

	mlem_value	val;

	val = mlem_parse_file(argv[1], (mlem_parser_settings){0});
	printf("Result: \n");
	if (val.type == TYPE_ARRAY)
		print_array(&val, 0);
	else
		printf("Object ?\n");

	return (0);
}
