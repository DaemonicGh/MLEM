
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "errors.h"

mlem_structure
DS_new(size_t ele_size)
{
	mlem_structure	ds	= {0};

	ds.data	= malloc((DS_BASE_CAPACITY + 1)  *ele_size);
	if (!ds.data)
	{
		error(NULL, ERR_MEMORY);
		return (ds);
	}
	bzero(ds.data, ele_size);
	ds.len		= 0;
	ds.capacity	= DS_BASE_CAPACITY;
	ds.span		= ele_size;
	return (ds);
}

bool
DS_resize(mlem_structure *ds, size_t new_capacity)
{
	void			*tmp;

	tmp = reallocarray(ds->data, new_capacity + 1, ds->span);
	if (!tmp && new_capacity > ds->capacity)
	{
		error(NULL, ERR_MEMORY);
		return (false);
	}

	ds->data 		= tmp;
	ds->capacity	= new_capacity;
	return (true);
}
