



#include "minishell.h"

void    sig_init(int    signum)
{
    (void)signum;
    if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

// void    sig_quit(int    signum)
// {
//     write(2, "Quit: ", 6);
//     ("%d", signum);
// 	write(2, "\n", 1);
// }

void    handler(void)
{
    signal(SIGINT, sig_init);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGQUIT, sig_quit);
}