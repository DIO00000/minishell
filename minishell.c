/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:39:52 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/21 23:25:45 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_init(t_minishell *minishell, char **env)
{
	(void)env;
	minishell->type = NULL;
	minishell->cmd_line = NULL;
	minishell->last_dir = NULL;
	minishell->env = env;
	minishell->defult_path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
							/usr/local/munki:/Library/Apple/usr/bin";
	minishell->input = NULL;
	minishell->pids = NULL;
	minishell->env_status = 0;
	minishell->syntax = 0;
	minishell->cmd_excuted = 1;
	minishell->trm_prompt = NULL;
	minishell->username = getenv("USER");
}

// void handle_signals(int sig) 
// {
// 	(void)sig;

//     printf("\n\033[1;33m➜ \033[1;34m minishell ♛ \033[0;m");
// } 

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	(void)ac;
	(void)av;

	if (!isatty(0))
		return (ft_error(NULL, "minishell: this input is not a tty"), 1);
	minishell_init(&minishell, env);
	while (1)
	{
		signals(&minishell.term);
		read_command(&minishell);
		// ft_lexer(&minishell);
		// ft_parser(&minishell);
		// ft_exit(&minishell);
	}
	// signal(SIGINT, handle_signals);
}