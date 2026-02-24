
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mlem.h"

static void
print_value_internal(mlem_value *val, int depth, bool preceded)
{
	char		tab[65] = {0};

	if (!preceded)
	{
		if (depth > 32) depth = 32;
		memset(tab, ' ', depth * 2);
		printf("%s", tab);
	}

	switch (val->type)
	{
		case TYPE_ARRAY:
			printf("[\n");
			for (size_t i = 0; val->val_array[i].type; i++)
				print_value_internal(&val->val_array[i], depth + 1, false);
			printf("%s]\n", tab);
			break ;

		case TYPE_OBJECT:
			printf("{\n");
			for (size_t i = 0; val->val_object[i].value.type; i++)
			{
				printf("\"%s\" = ", val->val_object[i].key);
				print_value_internal(&val->val_object[i].value, depth + 1, true);
			}
			printf("%s}\n", tab);
			break ;

		case TYPE_STRING:
			printf("\"%s\"\n", val->val_string);
			break ;

		case TYPE_NULL:
			printf("Null\n");
			break ;

		default:
			printf("???\n");
	}
}

void
mlem_print_value(mlem_value *val)
{
	print_value_internal(val, 0, false);
}

void
mlem_destroy_value(mlem_value *val, bool free_strings)
{
	switch (val->type) {

		case TYPE_ARRAY:
			for (size_t i = 0; val->val_array[i].type; i++)
				mlem_destroy_value(&val->val_array[i], free_strings);
			free(val->val_array);
			break ;

		case TYPE_OBJECT:
			for (size_t i = 0; val->val_object[i].value.type; i++)
			{
				if (free_strings)
					free(val->val_object[i].key);
				mlem_destroy_value(&val->val_object[i].value, free_strings);
			}
			free(val->val_object);
			break ;

		case TYPE_STRING:
			if (free_strings)
				free(val->val_string);
			break ;

		default: break ;
	}
	*val = MLEM_NULL_VALUE;
}
