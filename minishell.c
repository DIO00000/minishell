
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:02:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/23 22:26:32 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*mini_init(t_minishell *mini, t_list *data, char **env)
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
	mini->defult_path = malloc(90 * sizeof(char));
	mini->defult_path = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
	/usr/local/munki:/Library/Apple/usr/bin";
	data = fill_env(env, data, mini);
	mini->cmd_path = "./minishell";
	ft_shlvl(data, mini);
	return (data);
}

void	read_line(t_minishell *mini)
{
	// mini->input = readline(mini->trm_prompt);
	mini->input = readline(GREEN_ARROW X);
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
	t_list		*data;

	data = NULL;
	((void)ac, (void)av);
	if (!isatty(0))
		return (print_error(NULL, "this input is not a tty"), 1);
	data = mini_init(&mini, data, env);
	while (1)
	{
		signals(&mini.term);
		// prompt_custom(&mini);
		read_line(&mini);
		lexer(&mini);
		parsing(&mini);
		single_command((&mini)->input, &mini, &data);
		ft_exit(&mini, NULL, NULL, 0);
	}
}
