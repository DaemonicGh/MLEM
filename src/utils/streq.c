
#include <string.h>
#include <stdio.h>

#include "utils.h"

size_t
streq(const char *s1, const char *s2)
{
	size_t	i = 0;

	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i])
		return (0);
	return (i);
}

size_t
streq_list(const char *s, const char **sa)
{
	size_t	i;

	for (i = 0; sa[i]; i++)
	{
		if (streq(s, sa[i]))
			return (i);
	}
	return (ST_N1);
}
