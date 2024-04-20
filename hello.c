#include "minishell.h"
int main()
{
    // opendir("/Users/hbettal/Desktop/mini/parsing");
    // chdir("/Users/hbettal/Desktop/mini/parsing");
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("pwd before chdir: %s\n", pwd);
    chdir("/Users/hbettal/Desktop/mini/parsing");
    pwd = getcwd(NULL, 0);
    printf("pwd after chdir: %s\n", pwd);
    return (0);
}
