
#include "utils.h"

const char *
skip_potential_backslash(const char *s)
{
	if (*s == '\\')
		return (++s);
	return (s);
}

const char*
strchr_bs(const char *s, char c)
{
	for (; *s && *s != c; s++)
		s = skip_potential_backslash(s);
	if (*s == c)
		return (s);
	return (NULL);
}

const char*
strstr_bs(const char *s1, const char *s2)
{
	for (; (s1 = strchr_bs(s1, *s2)); s1++)
	{
	    if (streq(s1, s2))
			return (s1);
	}
	return (NULL);
}
