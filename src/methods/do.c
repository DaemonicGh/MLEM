
#include <stdlib.h>
#include "structures.h"

mlem_object
DO_new(void)
{
	return (DS_new(sizeof(mlem_pair)).object);
}

bool
DO_append(mlem_object *object, mlem_pair ele)
{
	mlem_structure	*structure = (mlem_structure *)object;

	if (object->len == object->capacity &&
		!DS_resize(structure, object->capacity * DS_GROW_RATIO))
		return (false);

	object->data[object->len++]				= ele;
	object->data[object->len]				= MLEM_NULL_PAIR;
	return (true);
}

void
DO_destroy(mlem_object *object, bool free_strings)
{
	for (size_t i = 0; i < object->len; i++)
	{
		if (free_strings)
			free(object->data[i].key);
		mlem_destroy_value(&object->data[i].value, free_strings);
	}
	free(object->data);
}
