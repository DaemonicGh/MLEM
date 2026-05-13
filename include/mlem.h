/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:29:30 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 23:36:12 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Enum representing the possible types of a value in the MLEM format.
 *
 * Types indicate the value's data type
 * and how it should be parsed and printed.
 *
 * TYPE_NONE represents an error and should not be used.
 */
typedef enum e_mlem_value_type: uint16_t
{
	MLEM_TYPE_NONE			= 0x0000,
	MLEM_TYPE_NULL			= 0x0001,
	MLEM_TYPE_INT			= 0x0010,
	MLEM_TYPE_FLOAT			= 0x0020,
	MLEM_TYPE_BOOL			= 0x0040,
	MLEM_TYPE_STRING		= 0x0100,
	MLEM_TYPE_REFERENCE		= 0x0400,
	MLEM_TYPE_ARRAY			= 0x1000,
	MLEM_TYPE_OBJECT		= 0x2000,
	MLEM_TYPE_TEMPLATE		= 0x4000
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

/**
 * Represents a value in the MLEM format.
 *
 * @type		indicates the value's type,
 * @[type]_v	contains the actual value.
 * Values specific to a type are prefixed with the type name.
 */
typedef struct s_mlem_value			t_mlem_value;

/**
 * Represents a key-value pair in the MLEM format,
 * used by objects.
 *
 * @key		the key of the pair,
 * @value	the value of the pair.
 */
typedef struct s_mlem_pair			t_mlem_pair;

/**
 * Represents a reference to a value in the MLEM format.
 *
 * @name		the name of the reference,
 * @ref_count	the number of values referencing this value,
 * @value		the value being referenced.
 */
typedef struct s_mlem_reference		*t_mlem_reference;

typedef struct s_mlem_value			t_mlem_template_struct;
typedef struct s_mlem_value			t_mlem_subtemplate;

/**
 * Represents a template in the MLEM format.
 *
 * @flags			the flags of the template,
 * @fallback		the fallback value of the template,
 * @subtemplates	the separate checks in the template.
 */
typedef struct s_mlem_template		*t_mlem_template;

/**
 * MLEM integer type.
 *
 * int_base is set to specify the base the intger was parsed from.
 */
typedef int64_t						t_mlem_int;

/**
 * MLEM float type.
 *
 * float_exponent is set to specify the exponent the float was parsed with.
 */
typedef double						t_mlem_float;

/**
 * MLEM boolean type.
 */
typedef bool						t_mlem_bool;

/**
 * MLEM string type.
 *
 * string_flavor is set to specify the type of the string.
 * string_len is set to specify the length of the string.
 * string_extra_capacity is set to specify the unused space in the allocation.
 */
typedef char						*t_mlem_string;

/**
 * MLEM array type.
 *
 * array_len is set to specify the length of the array.
 * array_extra_capacity is set to specify the unused space in the allocation.
 */
typedef t_mlem_value				*t_mlem_array;

/**
 * MLEM object type.
 *
 * object_len is set to specify the length of the object.
 * object_extra_capacity is set to specify the unused space in the allocation.
 */
typedef t_mlem_pair					*t_mlem_object;

struct s_mlem_value
{
	t_mlem_value_type		type;
	union
	{
		int16_t					int_base;
		int16_t					float_exponent;
		struct
		{
			uint8_t					string_extra_capacity;
			uint8_t					string_flavor;
		};
		bool					reference_owner;
		uint16_t				array_extra_capacity;
		uint16_t				object_extra_capacity;
		uint16_t				template_extra_capacity;
		uint16_t				__dummy_16;
	};
	union
	{
		uint32_t				string_len;
		uint32_t				array_len;
		uint32_t				object_len;
		uint32_t				template_len;
		uint32_t				__dummy_32;
	};
	union
	{
		t_mlem_int				int_v;
		t_mlem_float			float_v;
		t_mlem_bool				bool_v;
		t_mlem_string			string_v;
		t_mlem_reference		reference_v;
		t_mlem_array			array_v;
		t_mlem_object			object_v;
		t_mlem_template			template_v;
		void					*pointer_v;
		uint32_t				__dummy_v;
	};
};

struct s_mlem_reference
{
	t_mlem_string			name;
	uint32_t				ref_count;
	bool					is_implicit;
	t_mlem_value			value;
};

struct s_mlem_pair
{
	t_mlem_string			key;
	t_mlem_value			value;
};

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

struct s_mlem_template
{
	t_mlem_template_flag	flags;
	t_mlem_template_struct	structure;
	t_mlem_value			fallback;
	t_mlem_subtemplate		subtemplates[];
};

/**
 * Enum representing the possible errors that can occur
 * during MLEM parsing and evaluation.
 * When an error occurs, the returned value is of type 0
 * with the error code set in int_v.
 */
typedef enum e_mlem_error: uint32_t
{
	ERR_NONE,
	ERR_UNEXPECTED_ERROR,
	ERR_FILE,
	ERR_MEMORY,
	ERR_EMPTY_INPUT,
	ERR_INVALID_OUTER_REFERENCES,
	ERR_UNEXPECTED_TOKEN,
	ERR_INVALID_BACKSLASH,
	ERR_UNCLOSED_SYMBOL,
	ERR_UNCLOSED_STRUCTURE,
	ERR_WRONG_STRUCTURE_CLOSE,
	ERR_EXTRA_STRUCTURE_CLOSE,
	ERR_ASSIGN_IN_ARRAY,
	ERR_EXPECTED_ASSIGN,
	ERR_EXPECTED_VALUE,
	ERR_INVALID_STRING,
	ERR_INVALID_KEY,
	ERR_DUPLICATED_KEY,
	ERR_INVALID_NUMBER,
	ERR_EMPTY_NUMBER,
	ERR_INVALID_BASE_PREFIX,
	ERR_INVALID_BASE_NUMBER,
	ERR_NUMBER_OUT_OF_RANGE,
	ERR_NUMBER_TO_INFINITY,
	ERR_EMPTY_EXPONENT,
	ERR_INVALID_EXPONENT,
	ERR_UNDEFINED_REFERENCE,
	ERR_REDEFINING_REFERENCE,
	ERR_RECURSIVE_REFERENCE,
	ERR_REFERENCE_RECURSION_LIMIT,
	ERR_REDEFINING_TEMPLATE_FLAG,
	ERR_REDEFINING_TEMPLATE_RESTRICTOR,
	ERR_INVALID_SUBTEMPLATE,
	ERR_INVALID_SUBTEMPLATE_REFERENCE,
	ERR_INVALID_SUBTEMPLATE_STRUCTURE,
	ERR_MATCH_NO_MATCH,
	ERR_MATCH_WILDCARD,
	ERR_MATCH_REQUIRED,
	ERR_MATCH_OOB,
}	t_mlem_error;

// FUNCTIONS

/**
 * Opens and parses the given file and returns its root value.
 *
 * @filename	The path to the MLEM file.
 * @content		A pointer that will be set to the parsed string content.
 * @constants	A structure containing constants
 * that can be referenced by the file.
 *
 * The string content will be freed if the given pointer is NULL.
 */
t_mlem_value
mlem_parse(
	const char *filename,
	char **content,
	const t_mlem_value constants
	);

// VALUES

/**
 * Creates and returns a MLEM integer value.
 */
t_mlem_value
mlem_int(t_mlem_int value);

/**
 * Creates and returns a MLEM float value.
 */
t_mlem_value
mlem_float(t_mlem_float value);

/**
 * Creates and returns a MLEM boolean value.
 */
t_mlem_value
mlem_bool(t_mlem_bool value);

/**
 * Creates and returns a MLEM string value.
 */
t_mlem_value
mlem_string(t_mlem_string value);

/**
 * Creates and returns a MLEM null value.
 *
 * Do not confuse a null value with an absent value, which signifies an error.
 * A null value is perfectly fine to manipulate
 */
t_mlem_value
mlem_null(void);

/**
 * Returns the type of the given value or its reference.
 */
t_mlem_value_type
mlem_type(t_mlem_value value);

/**
 * Returns true if the two values or their references are equal.
 *
 * Two values are considered equal if they have the same type and value.
 * Pointers are compared by their memory address.
 */
bool
mlem_equal(t_mlem_value value1, t_mlem_value value2);

/**
 * Tweaks the type of the given value to the specified type.
 * Changes do not loose any data.
 * Use mlem_convert() if you're fine with data loss.
 * Returns false if no change was possible.
 */
bool
mlem_tweak(t_mlem_value *value, t_mlem_value_type type);

/**
 * Converts the given value to the specified type.
 * Changes may loose data.Use mlem_tweak() to only try lossless conversions.
 * Returns false if no change was possible.
 */
bool
mlem_convert(t_mlem_value *value, t_mlem_value_type type);

/**
 * Prints the given value recursively to the given file.
 */
void
mlem_print(FILE *file, t_mlem_value value);

/**
 * Prints the given value recursively to the specified file.
 * The file will be created if it does not exist, and overwritten otherwise.
 * Returns false if the file could not be opened or written to.
 */
bool
mlem_print_to_file(const char *filename, t_mlem_value value);

/**
 * Returns a deep copy of the given value.
 *
 * References are not copied, but are instead shared with the original value.
 * The returned value must be freed using mlem_destroy().
 */
t_mlem_value
mlem_copy(t_mlem_value value);

/**
 * Frees the memory used by the given value.
 *
 * References are only freed if there's no value referencing it.
 */
void
mlem_destroy(t_mlem_value value);

// REFERENCES

/**
 * Returns a new reference with the given name and value.
 */
t_mlem_value
mlem_reference(t_mlem_string name, t_mlem_value value);

/**
 * Returns the value of the given reference.
 */
t_mlem_value
mlem_dereference(t_mlem_value value);

/**
 * Returns the value of the given reference as a pointer.
 */
t_mlem_value
*mlem_dereference_ptr(t_mlem_value *value);

// ARRAYS

/**
 * Returns a new empty array with the given capacity.
 *
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_array_empty(uint32_t capacity);

/**
 * Returns a new array with the given values.
 *
 * Values must be of type t_mlem_value.
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_array(uint32_t len, ...);

/**
 * Resizes the given array to the given capacity.
 *
 * Returns true if the array was resized successfully, false otherwise.
 */
bool
mlem_array_resize(t_mlem_value *array, uint32_t capacity);

/**
 * Appends the given value to the given array.
 *
 * Returns true if the value was appended successfully, false otherwise.
 */
bool
mlem_array_append(t_mlem_value *array, t_mlem_value value);

/**
 * Returns the value at the given index in the given array.
 *
 * The value must be of type t_mlem_value.
 */
t_mlem_value
*mlem_array_get(t_mlem_value array, uint32_t index);

/**
 * Returns the index of the given value in the given array.
 *
 * Returns -1 if the value is not found.
 */
int64_t
mlem_array_index(t_mlem_value array, t_mlem_value value);

// OBJECTS

/**
 * Returns an empty object with the given capacity.
 *
 * The object must be freed using mlem_destroy().
 */
t_mlem_value
mlem_object_empty(uint32_t capacity);

/**
 * Returns an object with the given key-value pairs.
 *
 * Values must be of type t_mlem_pair.
 * The object must be freed using mlem_destroy().
 */
t_mlem_value
mlem_object(uint32_t len, ...);

/**
 * Resizes the given object to the given capacity.
 *
 * Returns true if the array was resized successfully, false otherwise.
 */
bool
mlem_object_resize(t_mlem_value *object, uint32_t capacity);

/**
 * Appends the given value to the given object.
 *
 * Returns true if the value was appended successfully, false otherwise.
 */
bool
mlem_object_append(
	t_mlem_value *object, t_mlem_string key, t_mlem_value value);

/**
 * Returns the value associated with the given key in the given object.
 *
 * Returns NULL if the key is not found.
 */
t_mlem_value
*mlem_object_get(t_mlem_value object, t_mlem_string key);

/**
 * Returns the key associated with the given value in the given object.
 *
 * Returns NULL if the value is not found.
 */
t_mlem_string
mlem_object_get_key(t_mlem_value object, t_mlem_value value);

/**
 * Returns the index of the given value in the given object.
 *
 * Returns -1 if the value is not found.
 */
int64_t
mlem_object_index(t_mlem_value object, t_mlem_value value);

/**
 * Returns the index of the given key in the given object.
 *
 * Returns -1 if the key is not found.
 */
int64_t
mlem_object_key_index(t_mlem_value object, t_mlem_string key);

// TEMPLATES

/**
 * Returns an empty template with the given capacity.
 *
 * The template must be freed using mlem_destroy().
 */
t_mlem_value
mlem_template_empty(uint32_t capacity);

/**
 * Returns a template with the given values.
 *
 * Values must be of type t_mlem_subtemplate.
 * The template must be freed using mlem_destroy().
 */
t_mlem_value
mlem_template(uint32_t len, ...);

/**
 * Resizes the given template to the given capacity.
 *
 * Returns true if the array was resized successfully, false otherwise.
 */
bool
mlem_template_resize(t_mlem_value *template, uint32_t capacity);

/**
 * Appends the given value to the given template.
 *
 * Returns true if the value was appended successfully, false otherwise.
 */
bool
mlem_template_append(t_mlem_value *template, t_mlem_subtemplate value);

/**
 * Matches the given value against the given template.
 *
 * Returns true if the value matches the template, false otherwise.
 */
bool
mlem_match_template(
	t_mlem_value *value, t_mlem_value *parent, t_mlem_value template);

// COMMON

/**
 * Returns the length of the given value.
 *
 * Returns 0 if the value is not an array, object, template or string.
 */
uint32_t
mlem_length(t_mlem_value value);

/**
 * Returns the value at the given path from the given value.
 *
 * The path is an array containing int and string values
 * specifying keys and indices.
 * Returns NULL if the value is not found.
 */
t_mlem_value
*mlem_get_from_path(t_mlem_value value, t_mlem_value path);

/**
 * Appends the given key-value pair to the given structure.
 *
 * The key is only necessary for objects.
 * Returns true if the value was appended successfully, false otherwise.
 * Returns false if the value isn't an array, object, or template.
 */
bool
mlem_append(t_mlem_value *structure,
	t_mlem_string key, t_mlem_value value);
