/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:02:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 15:45:21 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_init(t_minishell *mini)
{
	mini->input = NULL;
	mini->exit_status = 0;
	mini->env_status = 0;
	mini->pids = NULL;
	mini->cmd = NULL;
	mini->final_cmd = NULL;
	mini->new_env = NULL;
	mini->trm_prompt = NULL;
	mini->last_dir = NULL;
	mini->curr_dir = getcwd(NULL, 0);
	mini->username = getenv("USER");
	mini->lst = NULL;
}

void	read_line(t_minishell *mini)
{
	mini->input = readline(mini->trm_prompt);
	// mini->input = readline(GREEN_ARROW X);
	if (mini->input)
		add_history(mini->input);
	else
	{
		printf("exit\n");
		ft_exit(mini, NULL, NULL, 0);
		exit(mini->exit_status);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mini;

	((void)ac, (void)av, (void)env);
	mini_init(&mini);
	while (1)
	{
		signals(&mini.term);
		prompt_custom(&mini);
		read_line(&mini);
		lexer(&mini);
		parsing(&mini);
		ft_exit(&mini, NULL, NULL, 0);
	}
}
