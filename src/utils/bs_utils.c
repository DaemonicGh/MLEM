
#include <ctype.h>
#include <string.h>

#include "tokens.h"
#include "utils.h"

size_t
set_transformed_bs_sequence(const char *str, char *result)
{
	size_t	i = 0;
	size_t	j = 0;

	if (str[0] == 'x')
	{
		i = strnfind(number_values, toupper(str[1]), 15);
		if (i == ST_N1)
			return (ST_N1);
		j = strnfind(number_values, toupper(str[2]), 15);
		if (j == ST_N1)
			return (ST_N1);
		if (result)
		{
			result[0] = (i << 4) | j;
			result[1] = 0;
		}
		return (3);
	}

	if (str[0] == '0')
	{
		result[0] = 0;
		return (1);
	}

	while (backslash_transforms[i][0] &&
		!streq(str, backslash_transforms[i][0]))
		i++;
	if (!backslash_transforms[i][0])
		return (ST_N1);
	if (result)
	{
		while (backslash_transforms[i][1][j])
		{
			result[j] = backslash_transforms[i][1][j];
			j++;
		}
		result[j] = 0;
	}
	return (strlen(backslash_transforms[i][1]));
}

const char *
skip_potential_backslash(const char *s)
{
	if (*s == '\\' && *(s + 1))
		return (++s);
	return (s);
}