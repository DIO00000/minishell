/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:02:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/17 00:05:02 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_init(t_minishell *mini)
{
	mini->input = NULL;
	mini->env_status = 0;
	mini->pids = NULL;
	mini->cmd = NULL;
	mini->table = NULL;
	mini->new_env = NULL;
	mini->trm_prompt = NULL;
	mini->last_dir = NULL;
	mini->curr_dir = getcwd(NULL, 0);
	mini->username = getenv("USER");
	
}

void	read_line(t_minishell *mini)
{
	mini->input = readline(mini->trm_prompt);
	if (mini->input)
		add_history(mini->input);
	else
	{
		printf("exit\n");
		exit(mini->exit_status);
	}
}

int		main(int ac, char **av, char **env)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	(void)env;
	mini_init(&mini);
	while(1)
	{
		prompt_custom(&mini);
		read_line(&mini);
		signals(&mini.term);
		lexer(&mini);
		parsing(&mini);
	}
}