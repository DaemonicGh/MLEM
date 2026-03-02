
#pragma once

#include <stddef.h>
#include <stdbool.h>

#define ST_N1			(size_t)-1

size_t
streq(const char *s1, const char *s2);

size_t
strneq(const char *s1, const char *s2, size_t n);

size_t
streq_list(const char *s, const char* *sa);

size_t
strneq_list(const char *s, const char **sa, size_t n);

const char *
skip_potential_backslash(const char *s);

const char*
strchr_bs(const char *s, char c);

const char*
strstr_bs(const char *s1, const char *s2);

size_t
strfind(const char *s, char c);

size_t
strnfind(const char *s, char c, size_t n);

size_t
strnfindset(const char *s, char *set, size_t n);
