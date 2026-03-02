
#include <string.h>

#include "utils.h"

size_t
strfind(const char *s, char c)
{
	size_t	i = 0;

	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (ST_N1);
}

size_t
strnfind(const char *s, char c, size_t n)
{
	size_t	i = 0;

	while (s[i] && s[i] != c && n--)
		i++;
	if (s[i] == c)
		return (i);
	return (ST_N1);
}

size_t
strnfindset(const char *s, char *set, size_t n)
{
	size_t	i = 0;

	while (s[i] && !strchr(set, s[i]) && n--)
		i++;
	if (strchr(set, s[i]))
		return (i);
	return (ST_N1);
}