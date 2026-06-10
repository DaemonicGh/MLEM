/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .mlem_values.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:29:30 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:36:12 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Enum representing the bit mask of a MLEM type.
 *
 * TYPE_MASK_VARIANT	unique identifier for a type with that exact mask.
 * TYPE_MASK_CONTAINS	tells what kind of value is stored.
 * TYPE_MASK_USERSHIP	tells wether or not
 * the type is used by MLEM's API in any way.
 *
 * The 8th bit is currently unused.
 */
typedef enum e_mlem_value_type_mask: uint8_t
{
	MLEM_TYPE_MASK_VARIANT				= 0b00001111,
	MLEM_TYPE_MASK_CONTAINS				= 0b00110000,
	MLEM_TYPE_MASK_CONTAINS_IMMEDIATE	= 0b00000000,
	MLEM_TYPE_MASK_CONTAINS_POINTER		= 0b00010000,
	MLEM_TYPE_MASK_CONTAINS_ARRAY		= 0b00100000,
	MLEM_TYPE_MASK_CONTAINS_WRAPPED		= 0b00110000,
	MLEM_TYPE_MASK_USERSHIP				= 0b01000000,
	MLEM_TYPE_MASK_USERSHIP_MLEM		= 0b00000000,
	MLEM_TYPE_MASK_USERSHIP_USER		= 0b01000000,
}	t_mlem_value_type_mask;

/**
 * Enum representing the possible types of a value in the MLEM format.
 *
 * Types indicate the value's data type and how it should be handled.
 *
 * TYPE_NONE represents an error and should not be used.
 *
 * Type values follow this properties bit mask:
 * [0 | is_user | container_type[2] | variant[4]],
 * See MLEM_TYPE_MASK_ for more information.
 */
typedef enum e_mlem_value_type: uint8_t
{
	MLEM_TYPE_NONE			= 0b00000000,
	MLEM_TYPE_NULL			= 0b00000001,
	MLEM_TYPE_INT			= 0b00000010,
	MLEM_TYPE_FLOAT			= 0b00000011,
	MLEM_TYPE_BOOL			= 0b00000100,
	MLEM_TYPE_STRING		= 0b00010001,
	MLEM_TYPE_REFERENCE		= 0b00010010,
	MLEM_TYPE_ARRAY			= 0b00100001,
	MLEM_TYPE_PACKED_ARRAY	= 0b00100010,
	MLEM_TYPE_OBJECT		= 0b00100011,
	MLEM_TYPE_TEMPLATE		= 0b00110001,
	MLEM_TYPE_USER_POINTER	= 0b01010001,
}	t_mlem_value_type;

/**
 * Enum representing the possible flavors of a string value.
 *
 * Flavors indicate the type of string value being parsed,
 * how it should behave and how it should be printed.
 */
enum e_mlem_string_flavor: uint8_t
{
	MLEM_STR_UNQUOTED		= 0x01,
	MLEM_STR_QUOTED			= 0x02,
	MLEM_STR_DQUOTED		= 0x04,
	MLEM_STR_3QUOTED		= 0x08,
	MLEM_STR_3DQUOTED		= 0x10,
	MLEM_STR_MULTILINE		= (
		MLEM_STR_DQUOTED | MLEM_STR_3QUOTED | MLEM_STR_3DQUOTED),
	MLEM_STR_ESCAPE	= (
		MLEM_STR_UNQUOTED | MLEM_STR_QUOTED | MLEM_STR_DQUOTED),
	MLEM_STR_LENIENT_ESCAPE	= MLEM_STR_UNQUOTED
};

typedef union u_mlem_value			t_mlem_value;

typedef int64_t						t_mlem_int;
/**
 * MLEM integer value.
 *
 * @base	the base the integer was parsed from.
 */
typedef struct s_mlem_int_value
{
	t_mlem_value_type	type;
	int16_t				base;
	t_mlem_int			value;
}	t_mlem_int_value;

typedef double						t_mlem_float;
/**
 * MLEM float value.
 *
 * @exponent	the exponent the float was parsed with.
 */
typedef struct s_mlem_float_value
{
	t_mlem_value_type	type;
	int16_t				exponent;
	t_mlem_float		value;
}	t_mlem_float_value;

typedef bool						t_mlem_bool;
/**
 * MLEM boolean value.
 */
typedef struct s_mlem_bool_value
{
	t_mlem_value_type	type;
	t_mlem_bool			value;
}	t_mlem_bool_value;

typedef char						*t_mlem_string;
/**
 * MLEM string value.
 *
 * @flavor			the type of the string.
 * @len				the length of the string.
 * @extra_capacity	the unused elements in the allocation.
 */
typedef struct s_mlem_string_value
{
	t_mlem_value_type	type;
	uint8_t				extra_capacity;
	uint8_t				flavor;
	uint32_t			len;
	t_mlem_string		value;
}	t_mlem_string_value;

typedef struct s_mlem_reference		*t_mlem_reference;
/**
 * MLEM reference value.
 *
 * @is_owner	True if this value defined the reference.
 */
typedef struct s_mlem_reference_value
{
	t_mlem_value_type	type;
	bool				is_owner;
	t_mlem_reference	value;
}	t_mlem_reference_value;

typedef t_mlem_value				*t_mlem_array;
/**
 * MLEM array value.
 *
 * @len				the length of the array.
 * @extra_capacity	the unused elements in the allocation.
 */
typedef struct s_mlem_array_value
{
	t_mlem_value_type	type;
	uint16_t			extra_capacity;
	uint32_t			len;
	t_mlem_array		value;
}	t_mlem_array_value;

typedef struct s_mlem_pair			t_mlem_pair;
typedef t_mlem_pair					*t_mlem_object;
/**
 * MLEM object value.
 *
 * @len				the length of the object.
 * @extra_capacity	the unused elements in the allocation.
 */
typedef struct s_mlem_object_value
{
	t_mlem_value_type	type;
	uint16_t			extra_capacity;
	uint32_t			len;
	t_mlem_object		value;
}	t_mlem_object_value;

typedef struct s_mlem_template		*t_mlem_template;
/**
 * MLEM template value.
 *
 * @len				the length of the template.
 * @extra_capacity	the unused elements in the allocation.
 */
typedef struct s_mlem_template_value
{
	t_mlem_value_type	type;
	uint16_t			extra_capacity;
	uint32_t			len;
	t_mlem_template		value;
}	t_mlem_template_value;

/**
 * MLEM pointer value.
 *
 * This value is not used by MLEM, and exists for user convenience.
 * The pointer inside this value is not freed by mlem_destroy().
 */
typedef struct s_mlem_user_pointer_value
{
	t_mlem_value_type	type;
	void				*value;
}	t_mlem_user_pointer_value;

/**
 * MLEM packed array value.
 *
 * @element_type	the type of all the values in the array.
 * @len				the length of the array.
 * @extra_capacity	the unused elements in the allocation.
 *
 * Due to value header requirements, this array
 * cannot store structures and cannot own references.
 */
typedef struct s_mlem_packed_array_value
{
	t_mlem_value_type	type;
	t_mlem_value_type	element_type;
	uint16_t			extra_capacity;
	uint32_t			len;
	union
	{
		t_mlem_int			*value_int;
		t_mlem_float		*value_float;
		t_mlem_bool			*value_bool;
		t_mlem_string		*value_str;
		t_mlem_reference	*value_ref;
		void				**value_ptr;
	};
}	t_mlem_packed_array_value;

/**
 * Represents a value in the MLEM format.
 *
 * @type		shortcut to the value's type,
 * @[type]v		contains the actual value.
 */
typedef union u_mlem_value
{
	t_mlem_value_type			type;
	t_mlem_int_value			intv;
	t_mlem_float_value			floatv;
	t_mlem_bool_value			boolv;
	t_mlem_string_value			strv;
	t_mlem_reference_value		refv;
	t_mlem_array_value			arrayv;
	t_mlem_packed_array_value	packedv;
	t_mlem_object_value			objectv;
	t_mlem_template_value		templatev;
	t_mlem_user_pointer_value	ptrv;
	struct	s_mlem_value_raw_data
	{
		t_mlem_value_type	type;
		uint16_t			data16;
		uint32_t			data32;
		uint64_t			value;
	}					_datav;
}	t_mlem_value;

/**
 * Represents a reference to a value in the MLEM format.
 *
 * @name		the name of the reference,
 * @ref_count	the number of values referencing this value,
 * @value		the value being referenced.
 */
typedef struct s_mlem_reference
{
	t_mlem_string			name;
	uint32_t				ref_count;
	bool					is_implicit;
	t_mlem_value			value;
}	*t_mlem_reference;

/**
 * Represents a key-value pair in the MLEM format, used by objects.
 *
 * @key		the key of the pair,
 * @value	the value of the pair.
 */
typedef struct s_mlem_pair
{
	t_mlem_string			key;
	t_mlem_value			value;
}	t_mlem_pair;

typedef enum e_mlem_template_flag: uint32_t
{
	MLEM_TPF_NONE			= 0x0000,
	MLEM_TPF_REQUIRED		= 0x0001,
	MLEM_TPF_STRICT_TYPE	= 0x0002,
	MLEM_TPF_STRICT_BOUNDS	= 0x0004,
	MLEM_TPF_NO_REFERENCE	= 0x0010,
	MLEM_TPF_NO_WILDCARD	= 0x0020,
	MLEM_TPF_CLAMP			= 0x0100,
	MLEM_TPF_CONVERT		= 0x0200,
	MLEM_TPF_FLATTEN		= 0x0400,
}	t_mlem_template_flag;

typedef union u_mlem_value			t_mlem_subtemplate;
/**
 * Represents a template in the MLEM format.
 *
 * @flags			the flags of the template,
 * @fallback		the fallback value of the template,
 * @subtemplates	the separate checks in the template.
 */
typedef struct s_mlem_template
{
	t_mlem_template_flag	flags;
	t_mlem_value			fallback;
	t_mlem_subtemplate		subtemplates[];
}	*t_mlem_template;

// TYPE ASSERTIONS

static_assert(sizeof(t_mlem_int) == 8,
	"Invalid MLEM integer size, expected 8 byte value");
static_assert(sizeof(t_mlem_float) == 8,
	"Invalid MLEM float size, expected 8 byte value");
static_assert(sizeof(t_mlem_bool) == 1,
	"Invalid MLEM boolean size, expected 1 byte value");
static_assert(sizeof(void *) == 8,
	"Invalid MLEM pointer size, expected 8 byte value");
static_assert(sizeof(t_mlem_value) == 16,
	"Invalid MLEM value size, expected 16 byte value");
