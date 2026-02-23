
#include "mlem.h"

#define MLEM_NULL_TOKEN	(mlem_token){0}

#define ST_N1			(size_t)-1

typedef enum {
	ERR_EMPTY,

	ERR_UNEXPECTED_ERROR,

	ERR_FILE,
	ERR_MEMORY,

	ERR_UNEXPECTED_TOKEN,

	ERR_UNCLOSED_STRUCTURE,
	ERR_WRONG_STRUCTURE_CLOSE,
	ERR_ASSIGN_IN_ARRAY,

}	mlem_errors;

typedef struct {
	char*					content;
	mlem_parser_settings	settings;
	size_t					line;
	size_t					column;
	size_t					depth;
}	mlem_context;

typedef enum
{
	TK_NULL,

	TK_WORD				= 1 << 0,

	TK_OPEN_UNKNOWN		= 1 << 1,
	TK_CLOSE_UNKNOWN	= 1 << 2,
	TK_OPEN_ARRAY		= 1 << 3,
	TK_CLOSE_ARRAY		= 1 << 4,
	TK_OPEN_OBJECT		= 1 << 5,
	TK_CLOSE_OBJECT		= 1 << 6,

	TK_ASSIGN			= 1 << 7,

	TK_WORD_DEL			= 1 << 8,
	TK_ML_WORD_DEL		= 1 << 9,

	TK_COMMENT			= 1 << 10,
	TK_ML_COMMENT_DEL	= 1 << 11,
	TK_ML_COMMENT_START	= 1 << 12,
	TK_ML_COMMENT_END	= 1 << 13,

}	mlem_token_type;

typedef enum
{
	TKG_OPEN			= TK_OPEN_UNKNOWN | TK_OPEN_ARRAY | TK_OPEN_OBJECT,
	TKG_CLOSE			= TK_CLOSE_UNKNOWN | TK_CLOSE_ARRAY | TK_CLOSE_OBJECT,

	TKG_VALUE			= TK_WORD | TKG_OPEN | TKG_CLOSE,
	TKG_SIGNIFICANT		= TKG_VALUE | TK_ASSIGN,
}	mlem_token_type_group;

typedef struct {
	mlem_token_type	type;
	size_t			line;
	size_t			column;
	size_t			depth;
	char*			val;
	const char*		trigger;
	size_t			len;
}	mlem_token;

typedef struct {
	mlem_value*	data;
	size_t		len;
	size_t		capacity;
	size_t		span;
}	mlem_array;

typedef struct {
	mlem_pair*	data;
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

#define DS_BASE_CAPACITY	4
#define DS_GROW_RATIO		2.0

#define DA_VALUE_SIZE		sizeof(mlem_value)
#define DO_VALUE_SIZE		sizeof(mlem_pair)

// Globals
static const char*	error_messages[] = {
	"",
	"Unexpected error",
	"Unable to open file",
	"Memory error",
	"Unexpected Token",
	"Unclosed structure",
	"Incorrect closing symbol",
	"Object assignment in array"
};

static const char*	token_triggers[] = {
	"'''", "///", "\"\"\"",
	"//", "/*", "*/",
	"[", "]", "=", "'", "\"",
	"{", "}", ":", NULL
};

static const mlem_token_type	token_trigger_values[] = {
	TK_ML_WORD_DEL, TK_ML_COMMENT_DEL, TK_ML_WORD_DEL,
	TK_COMMENT, TK_ML_COMMENT_START, TK_ML_COMMENT_END,
	TK_OPEN_UNKNOWN, TK_CLOSE_UNKNOWN, TK_ASSIGN, TK_WORD_DEL, TK_ML_WORD_DEL,
	TK_OPEN_OBJECT, TK_CLOSE_OBJECT, TK_ASSIGN, TK_NULL
};

static const char* token_trigger_ends[] ={
	"'''", "///", "\"\"\"",
	"\n", "*/", NULL,
	NULL, NULL, NULL, "'", "\"",
	NULL, NULL, NULL, NULL
};

static const char*	skip_triggers[] = {
	" ", "\t", "\n", ",", NULL
};
static const char*	token_repr[] = {
	"N", "W", "[", "]", "(", ")", "{", "}", "=", "'", "\"", "//", "///", "/*", "*/", NULL
};

static const size_t	DO_elememt_sizes[] = {
	0, sizeof(mlem_value), sizeof(mlem_pair)
};

//

static inline void
error(mlem_errors type);

static mlem_structure
DS_new(size_t ele_size);

static inline mlem_array
DA_new(void);

static inline mlem_object
DO_new(void);

static bool
DS_grow(mlem_structure *ds);

static bool
DA_append(mlem_array *array, mlem_value ele);

static bool
DO_append(mlem_object *object, mlem_pair ele);

static void
DS_destroy(mlem_structure *ds);

static size_t
streq(const char* s1, const char* s2);

static size_t
streq_list(const char* s, const char** sa);

static const char*
strchr_bs(const char *s, char c);

static const char*
strstr_bs(const char *s1, const char *s2);

static inline mlem_context
context_at_token(mlem_context *mlem, mlem_token *token);

static void
print_token(mlem_token_type token);

static bool
move_forward(mlem_context *mlem, size_t amount);

static bool
move_past_blank(mlem_context *mlem);

static void
move_past_statement(mlem_context *mlem, mlem_token *token);

static mlem_token
get_next_token(mlem_context *mlem);

static mlem_value
parse_array(mlem_context *mlem, mlem_token *trigger_token);


static mlem_token_type
get_structure_type(mlem_context *mlem);

static mlem_value
parse_structure(mlem_context *mlem, mlem_token *trigger_token);

static void
parse_start(mlem_context *mlem);

static char*
open_and_read_file(const char *filename);
