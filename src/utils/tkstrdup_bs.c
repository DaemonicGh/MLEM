
#include "context.h"
#include "errors.h"
#include "tokens.h"
#include "utils.h"
#include <stdlib.h>

char
*mlem_tkstrndup_bs(mlem_context *mlem, mlem_token *token)
{
	char	*str;
	size_t	i = 0;
	size_t	j = 0;
	size_t	len;

	str = malloc(token->len + 1);
	if (!str)
	{
		set_error(ERR_MEMORY);
		return (NULL);
	}
	while (i < token->len)
	{
		if (token->val[i] == '\\')
		{
			i++;
			len = set_transformed_bs_sequence(token->val + i, str + j);
			if (len == ST_N1)
			{
				set_error_t(mlem, token, ERR_INVALID_BACKSLASH);
				free(str);
				return (NULL);
			}
			i += len;
			while (str[j])
				j++;
		}
		else
			str[j++] = token->val[i++];
	}
	str[j] = 0;
	return (str);
}