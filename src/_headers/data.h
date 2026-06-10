/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprieur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:23:28 by rprieur           #+#    #+#             */
/*   Updated: 2026/05/09 03:58:34 by rprieur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <math.h>
#include <stdint.h>

#include "mlem.h"

#define STRUCTURE_BASE_CAPACITY				2
#define STRUCTURE_GROW_RATIO				2

#define PRINT_TAB_SIZE						4

typedef enum e_mlem_token_type: uint32_t
{
	TKN_ERROR				= 0x000000,
	TKN_UNEXPECTED			= 0x000001,
	TKN_SKIP				= 0x000002,
	TKN_BACKSLASH			= 0x000004,
	TKN_EOF					= 0x000008,
	TKN_CONTINUE			= 0x000010,
	TKN_COMMENT				= 0x000020,
	TKN_WORD				= 0x000100,
	TKN_NUMBER				= 0x000200,
	TKN_STRING				= 0x000400,
	TKN_REFERENCE			= 0x001000,
	TKN_STATEMENT			= 0x002000,
	TKN_OPEN				= 0x010000,
	TKN_CLOSE				= 0x020000,
	TKN_ASSIGN				= 0x040000,
}	t_mlem_token_type;

enum e_mlem_token_type_group: uint32_t
{
	TKG_TEXT				= TKN_WORD | TKN_NUMBER | TKN_STRING,
	TKG_OPEN				= TKN_OPEN,
	TKG_CLOSE				= TKN_CLOSE | TKN_EOF,
	TKG_UNSIGNIFICANT		= (TKN_SKIP
		| TKN_BACKSLASH | TKN_CONTINUE | TKN_COMMENT),
	TKG_VALUE				= TKG_TEXT | TKN_REFERENCE | TKG_OPEN,
	TKG_STRUCTURE_VALUE		= TKG_VALUE | TKG_CLOSE,
	TKG_ARRAY_VALUE			= TKG_VALUE | TKG_CLOSE,
	TKG_OBJECT_KEY			= TKN_WORD | TKN_STRING | TKN_REFERENCE | TKG_CLOSE,
	TKG_OBJECT_VALUE		= TKG_VALUE,
	TKG_TEMPLATE_FLAG		= TKN_WORD | TKN_REFERENCE | TKG_OPEN | TKG_CLOSE,
	TKG_SUBTEMPLATE			= TKG_TEMPLATE_FLAG | TKN_ASSIGN,
	TKG_TEMPLATE_FALLBACK	= TKG_VALUE,
};

enum e_mlem_token_trigger
{
	TRG_NONE = 0,
	TRG_UNEXPECTED,
	TRG_ST_COMMENT_END,
	TRG_SKIP,
	TRG_NEWLINE,
	TRG_BACKSLASH,
	TRG_EOF,
	TRG_CONTINUE,
	TRG_SS_COMMENT,
	TRG_SSS_COMMENT,
	TRG_ST_COMMENT_START,
	TRG_WORD,
	TRG_NUMBER,
	TRG_Q_STRING,
	TRG_DQ_STRING,
	TRG_3Q_STRING,
	TRG_3DQ_STRING,
	TRG_REFERENCE,
	TRG_ASSIGN,
	TRG_OPEN_STRUCTURE,
	TRG_OPEN_ARRAY,
	TRG_OPEN_PACKED_ARRAY,
	TRG_P_OPEN_PACKED_ARRAY,
	TRG_OPEN_OBJECT,
	TRG_OPEN_TEMPLATE,
	TRG_CLOSE_STRUCTURE,
	TRG_CLOSE_ARRAY,
	TRG_CLOSE_OBJECT,
	TRG_CLOSE_TEMPLATE,
};

enum e_mlem_token_trigger_data: uint8_t
{
	TRGDATA_STRUCTURE		= 0x01,
	TRGDATA_ARRAY			= 0x02,
	TRGDATA_PACKED_ARRAY	= 0x04,
	TRGDATA_OBJECT			= 0x08,
	TRGDATA_TEMPLATE		= 0x10,
};

#define TRIGGER_BLACKLIST_COUNT	3
#define TRIGGER_ERRORLIST_COUNT	2
#define TRIGGER_MAX_VALUE_LEN	5

typedef const struct s_mlem_token_trigger
{
	const t_mlem_token_type	type;
	const uint32_t			whitelist;
	const uint8_t			data;
	const uint8_t			trg_blacklist[TRIGGER_BLACKLIST_COUNT];
	const uint8_t			trg_errorlist[TRIGGER_ERRORLIST_COUNT];
	const char				value[TRIGGER_MAX_VALUE_LEN];
	const uint8_t			len;
}	t_mlem_token_trigger;

#define CONSTANT_MAX_NAME_LEN	8

typedef const struct s_mlem_constant
{
	char						name[CONSTANT_MAX_NAME_LEN];
	t_mlem_value				value;
}	t_mlem_constant;

#define TOKEN_COUNT				32
#define CONSTANT_ARRAY_COUNT	8
#define CONSTANT_COUNT			3
#define CHAR_COUNT				128
#define CHAR_TOKEN_COUNT		4
#define MAX_NUMBER_BASE			32
#define FLAVOR_COUNT			17
#define MAX_FLAVOR_STR_LEN		17

struct s_mlem_data
{
	t_mlem_token_trigger			tokens[TOKEN_COUNT];
	t_mlem_constant					constants[
		CONSTANT_ARRAY_COUNT][CONSTANT_COUNT];
	struct s_mlem_char_data
	{
		uint8_t						tokens[CHAR_COUNT][CHAR_TOKEN_COUNT];
		int8_t						constants[CHAR_COUNT];
		char						transform[CHAR_COUNT];
		int8_t						number[CHAR_COUNT];
		int8_t						base[CHAR_COUNT];
	}							char_data;
	struct s_mlem_repr_data
	{
		char						transform[CHAR_COUNT];
		char						number[MAX_NUMBER_BASE + 1];
		char						base[MAX_NUMBER_BASE + 1];
		char						flavor[FLAVOR_COUNT][MAX_FLAVOR_STR_LEN];
	}							repr_data;
};

extern const struct s_mlem_data				g_mlem_data;

// TEMPLATES

typedef struct s_mlem_template_flag_def
{
	t_mlem_template_flag		type;
	t_mlem_template_flag		blacklist;
	const char					*values[4];
}	t_mlem_template_flag_def;

extern const t_mlem_template_flag_def		g_template_flags[];

typedef struct s_mlem_subtemplate_trigger
{
	const char					*triggers[4];
	t_mlem_value_type			type;
	t_mlem_int					range[2];
}	t_mlem_subtemplate_trigger;

extern const t_mlem_subtemplate_trigger		g_template_structures[];
extern const t_mlem_subtemplate_trigger		g_subtemplates[];

// ERRRORS

typedef enum e_mlem_error: uint32_t
{
	ERR_NONE,
	ERR_UNEXPECTED_ERROR,
	ERR_MEMORY,
	ERR_FILE,
	ERR_EMPTY_FILE,
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
	ERR_EMPTY_PACKED_ARRAY,
	ERR_INVALID_PACKED_TYPE_DEFINITION,
	ERR_INVALID_PACKED_TYPE,
	ERR_INVALID_PACKED_TYPE_INT_FLOAT,
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

#define ASCII_ERR0						"\x1B[0;1;4;31m"
#define ASCII_ERR1						"\x1B[0;1;31m"
#define ASCII_ERR2						"\x1B[0;4;31m"
#define ASCII_ERR3						"\x1B[0;31m"
#define ASCII_ERR4						"\x1B[0;1;2;31m"
#define ASCII_TXT1						"\x1B[0m"
#define ASCII_TXT2						"\x1B[0;2m"
#define ASCII_RESET						"\x1B[0m"

extern const char							*g_error_messages[][2];
