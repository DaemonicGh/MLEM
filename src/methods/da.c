
#include <stdlib.h>
#include "mlem.h"
#include "structures.h"

mlem_array
DA_new(void)
{
	return (DS_new(sizeof(mlem_value)).array);
}

bool
DA_append(mlem_array *array, mlem_value ele)
{
	mlem_structure	*structure	= (mlem_structure *)array;

	if (array->len == array->capacity &&
		!DS_resize(structure, array->capacity * DS_GROW_RATIO))
		return (false);

	array->data[array->len++]	= ele;
	array->data[array->len]		= MLEM_NULL_VALUE;
	return (true);
}

void
DA_destroy(mlem_array *array, bool free_strings)
{
	for (size_t i = 0; i < array->len; i++)
		mlem_destroy_value(&array->data[i], free_strings);
	free(array->data);
}
