
#pragma once

#include "mlem.h"

#define DS_BASE_CAPACITY	4
#define DS_GROW_RATIO		2.0
#define DS_CROP_THRESHOLD	16

#define DA_VALUE_SIZE		sizeof(mlem_value)
#define DO_VALUE_SIZE		sizeof(mlem_pair)

typedef struct {
	mlem_value	*data;
	size_t		len;
	size_t		capacity;
	size_t		span;
}	mlem_array;

typedef struct {
	mlem_pair	*data;
	size_t		len;
	size_t		capacity;
	size_t		span;
}	mlem_object;

typedef union {
	mlem_array	array;
	mlem_object	object;
	struct {
		void		*data;
		size_t		len;
		size_t		capacity;
		size_t		span;
	};
}	mlem_structure;

mlem_structure
DS_new(size_t ele_size);

bool
DS_resize(mlem_structure *ds, size_t new_capacity);

mlem_array
DA_new(void);

bool
DA_append(mlem_array *array, mlem_value ele);

void
DA_destroy(mlem_array *array, bool free_strings);

mlem_object
DO_new(void);

bool
DO_append(mlem_object *object, mlem_pair ele);

void
DO_destroy(mlem_object *object, bool free_strings);
