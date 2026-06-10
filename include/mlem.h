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

//  ▒▒▒▒▒▒  ██▄    ▄██ ███       ████████████▄    ▄██
//  ▒▒      ████▄▄████  ██       ▀▀         ▀██▄▄████
//  ▒▒      ██ ▀██▀ ██  ██       ██████    █▄ ▀██▀ ██     ▒▒
//  ▒▒      ██      ██  ██       ██        ██      ██     ▒▒
//  ▒▒      ██      ██  ██       ▀▀        ██      ██     ▒▒▒▒▒
//  ▒▒▒▒▒▒  ██      ███ █████████████████  ██      ██  ▒▒ ▒▒ ▒▒

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include ".mlem_values.h"

// PARSE

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

// SERIALIZE

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

// CREATE

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
 * Creates and returns a MLEM string value with the given attributes.
 */
t_mlem_value
mlem_string_ex(t_mlem_string value, uint32_t len, uint8_t flavor);

/**
 * Creates and returns a MLEM null value.
 *
 * Do not confuse a null value with
 * an absent/none value, which signifies an error.
 * A null value is perfectly fine to manipulate
 */
t_mlem_value
mlem_null(void);

/**
 * Returns a new empty array with the given capacity.
 *
 * The array allocation can fail, then
 * the returned value will be zero padded.
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_array_empty(uint32_t capacity);

/**
 * Returns a new array with the given values.
 *
 * The array allocation can fail, then
 * the returned value will be zero padded.
 * Values must be of type t_mlem_value.
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_array(uint32_t len, ...);

/**
 * Returns a new empty packed array
 * for the given type with the given capacity.
 *
 * The array allocation can fail, then
 * the returned value will be zero padded.
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_packed_array_empty(t_mlem_value_type type, uint32_t capacity);

/**
 * Returns a new packed array for the given type with the given values.
 *
 * The array allocation can fail, then
 * the returned value will be zero padded.
 * Values must be of the specified type.
 * The array must be freed using mlem_destroy().
 */
t_mlem_value
mlem_packed_array(t_mlem_value_type type, uint32_t len, ...);

/**
 * Returns an empty object with the given capacity.
 *
 * The object allocation can fail, then
 * the returned value will be zero padded.
 * The object must be freed using mlem_destroy().
 */
t_mlem_value
mlem_object_empty(uint32_t capacity);

/**
 * Returns an object with the given key-value pairs.
 *
 * The object allocation can fail, then
 * the returned value will be zero padded.
 * Values must be of type t_mlem_pair.
 * The object must be freed using mlem_destroy().
 */
t_mlem_value
mlem_object(uint32_t len, ...);

/**
 * Creates and returns a MLEM value
 * with the specified type and value.
 */
t_mlem_value
mlem_raw_value(t_mlem_value_type type, uint64_t value);

/**
 * Creates and returns a MLEM value
 * with the specified type, value and metadata.
 */
t_mlem_value
mlem_raw_value_ex(t_mlem_value_type type,
	uint64_t value, uint32_t data_32, uint16_t data_16);

// CONVERT

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
 * Changes may loose data. Use mlem_tweak() to only try lossless conversions.
 * Returns false if no change was possible.
 */
bool
mlem_convert(t_mlem_value *value, t_mlem_value_type type);

/**
 * Tweaks and returns the given value pointer
 * to have the same type as the fallback.
 *
 * The value can't be tweaked or
 * if the value is NULL, the fallback is returned.
 */
t_mlem_value
mlem_fallback(t_mlem_value *value, t_mlem_value fallback);

/**
 * Tweaks and returns the given value as an integer.
 *
 * The value can't be tweaked, or
 * if the value is NULL, the fallback is returned.
 */
t_mlem_int
mlem_as_int(t_mlem_value *value, t_mlem_int fallback);

/**
 * Tweaks and returns the given value as a float.
 *
 * The value can't be tweaked, or
 * if the value is NULL, the fallback is returned.
 */
t_mlem_float
mlem_as_float(t_mlem_value *value, t_mlem_float fallback);

/**
 * Tweaks and returns the given value as a boolean.
 *
 * The value can't be tweaked, or
 * if the value is NULL, the fallback is returned.
 */
t_mlem_bool
mlem_as_bool(t_mlem_value *value, t_mlem_bool fallback);

/**
 * Tweaks and returns the given value as a string.
 *
 * The value can't be tweaked, or
 * if the value is NULL, the fallback is returned.
 */
t_mlem_string
mlem_as_string(t_mlem_value *value, t_mlem_string fallback);

// VALUES

/**
 * Returns the type of the given value or its reference.
 */
t_mlem_value_type
mlem_type(t_mlem_value value);

/**
 * Returns true if the given value's type matches one of the given type.
 *
 * @count	The amount of type to check for.
 */
bool
mlem_is_type(t_mlem_value value, uint32_t count, ...);

/**
 * Returns true if the two values are equal.
 *
 * Two values are considered equal if they have the same type and value.
 * Pointers are compared by their memory address.
 */
bool
mlem_equal(t_mlem_value value1, t_mlem_value value2);

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

/**
 * Frees the memory used by the given value, following the given parameters.
 *
 * References are only freed if there's no value referencing it.
 */
void
mlem_destroy_ex(t_mlem_value value,
	bool free_keys, bool free_strings, bool free_ref_names);

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

// REFERENCES

/**
 * Returns a new reference with the given name and value.
 *
 * The reference allocation can fail, then
 * the returned value will be zero padded.
 * The reference must be freed using mlem_destroy().
 */
t_mlem_value
mlem_reference_create(t_mlem_string name, t_mlem_value value);

/**
 * Returns a copy of the given reference value.
 *
 * The value must be freed using mlem_destroy().
 */
t_mlem_value
mlem_reference(t_mlem_value reference);

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
 * Returns NULL if the index is out of bounds
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

// PACKED ARRAYS

/**
 * Resizes the given packed array to the given capacity.
 *
 * Returns true if the array was resized successfully, false otherwise.
 */
bool
mlem_packed_array_resize(t_mlem_value *array, uint32_t new_capacity);

/**
 * Appends the given value to the given packed array.
 *
 * Returns true if the given value has the proper type
 * and the value was appended successfully, returns false otherwise.
 */
bool
mlem_packed_array_append(t_mlem_value *array, t_mlem_value value);

/**
 * Returns the value at the given index in the given packed array.
 *
 * The value is returned inside a mlem value specifying its type.
 * The returned value will be zero padded if the index is out of bounds
 */
t_mlem_value
mlem_packed_array_get(t_mlem_value array, uint32_t index);

/**
 * Returns the index of the given value in the given packed array.
 *
 * Returns -1 if the value is not found.
 */
int64_t
mlem_packed_array_index(t_mlem_value array, t_mlem_value value);

/**
 * Sets the value at the given index in the given packed array
 * to the value stored in the given mlem value.
 *
 * Returns false if the index is out of bounds
 * or if the value has the wrong type.
 */
bool
mlem_packed_array_set(
	t_mlem_value array, uint32_t index, t_mlem_value value);

// OBJECTS

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
 * Allocates the given key on the heap and
 * appends the given value to the given object.
 *
 * Returns true if the value was appended successfully, false otherwise.
 */
bool
mlem_object_alloc_append(
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
