
#pragma once

#include <stddef.h>

#define ST_N1			(size_t)-1

size_t
streq(const char *s1, const char *s2);

size_t
streq_list(const char *s, const char* *sa);

const char *
skip_potential_backslash(const char *s);

const char*
strchr_bs(const char *s, char c);

const char*
strstr_bs(const char *s1, const char *s2);
