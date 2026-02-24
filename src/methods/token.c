
#include <stdio.h>
#include "tokens.h"

void
print_token(mlem_token_type token)
{
	size_t	i = (token != 0);

	for (; token > 1; i++)
		token >>= 1;
	printf("%s", token_repr[i]);
}
