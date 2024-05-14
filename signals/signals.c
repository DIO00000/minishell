



// #include "minishell.h"

// void    sig_init(int    signum)
// {
//     (void)signum;
//     if (waitpid(-1, NULL, WNOHANG) == 0)
// 		return ;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// }

// // void    sig_quit(int    signum)
// // {
// //     write(2, "Quit: ", 6);
// //     ft_putnbr_fd(signum, 2);
// // 	write(2, "\n", 1);
// // }

// void    handler(void)
// {
//     signal(SIGINT, sig_init);
//     signal(SIGQUIT, SIG_IGN);
// }

#include "../minishell.h"

void	signals(struct termios *term)
{
	remove_c(term);
	signal(SIGINT, sig_init);
	signal(SIGQUIT, SIG_IGN);
}

void	remove_c(struct termios *term)
{
	struct termios	term_removal;

	tcgetattr(1, term);
	tcgetattr(1, &term_removal);
	term_removal.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &term_removal);
}

void    sig_init(int    signum)
{
    if (signum == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
