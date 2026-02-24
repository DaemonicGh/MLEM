
#include "tokens.h"
#include "utils.h"

const mlem_token_trigger
*get_trigger(const char *s)
{
	size_t	i;

	for (i = 0; token_triggers[i].type; i++)
	{
		if (multistreq(s, token_triggers[i].start))
			return (&token_triggers[i]);
	}
	return (NULL);
}
