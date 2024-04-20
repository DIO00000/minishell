#include "minishell.h"
int main()
{
    char **sp;

    sp = split_token("cat");
    printf("%s\n", sp[0]);
    printf("%s\n", sp[1]);
    printf("%s\n", sp[2]);
}