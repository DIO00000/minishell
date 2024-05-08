
#include "minishell.h"

int main()
{
	char *l = "ls -la > f";

	printf("%s\n", *split_token(l));
}