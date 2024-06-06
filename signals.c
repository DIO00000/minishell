/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:15:24 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 12:39:52 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_s = 0;


void	signals(t_minishell *mini)
{
	remove_c(&mini->term);
	signal(SIGINT, sig_init);
	signal(SIGQUIT, SIG_IGN);
	if (g_exit_s == 1 || g_exit_s == 131)
		mini->exit_status = g_exit_s;
	g_exit_s = 0;
}

void	remove_c(struct termios *term)
{
	struct termios	term_removal;

	tcgetattr(1, term);
	tcgetattr(1, &term_removal);
	term_removal.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &term_removal);
}

void	sig_init(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_s = 1;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_quit(int signum)
{
	g_exit_s = 131;
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putchar_fd('\n', 2);
}
