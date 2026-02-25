
#include "tokens.h"
#include "utils.h"

mlem_token_trigger
*get_start_trigger(const char *s)
{
	size_t	i;

	for (i = 0; token_triggers[i].type; i++)
	{
		if (streq_list(s, (const char **)token_triggers[i].start) != ST_N1)
			return (&token_triggers[i]);
	}
	return (NULL);
}

mlem_token_trigger
*get_start_trigger_p(const char *s, const char **trigger_str)
{
	size_t	pos;
	size_t	i;

	for (i = 0; token_triggers[i].type; i++)
	{
		pos = streq_list(s, (const char **)token_triggers[i].start);
		if (pos == ST_N1)
			continue ;
		*trigger_str = token_triggers[i].start[pos];
		return (&token_triggers[i]);
	}
	return (NULL);
}
