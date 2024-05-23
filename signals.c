/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:15:24 by oelharbi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/22 21:17:16 by oelharbi         ###   ########.fr       */
=======
/*   Updated: 2024/05/22 16:13:54 by oelharbi         ###   ########.fr       */
>>>>>>> 97a5cd5fc7872c57f0cac5beec0a4ec30d606f33
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sig_init(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_quit(int signum)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putchar_fd('\n', 2);
}
