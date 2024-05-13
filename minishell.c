/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 04:28:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/13 00:49:47 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*minishell_init(t_minishell *minishell, t_list *data, char **env)
{
	minishell->cmd = NULL;
	minishell->last_dir = NULL;
	minishell->curr_dir = getcwd(NULL, 0);
	minishell->defult_path = malloc(90 * sizeof(char));
	minishell->defult_path = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki:/Library/Apple/usr/bin";
	minishell->pids = NULL;
	minishell->env_status = 0;
	minishell->syntax = 0;
	minishell->cmd_excuted = 1;
	minishell->trm_prompt = NULL;
	minishell->username = getenv("USER");
	minishell->cmd_path = "./minishell";
	minishell->trimed_cmd = NULL;
	minishell->exit_status = 0;
	data = fill_env(env, data, minishell);
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;
	t_list		*data;

	data = NULL;
	(void)ac;
	(void)av;

	if (!isatty(0))
		return (ft_error(NULL, "minishell: this input is not a tty"), 1);
	data = minishell_init(&minishell, data, env);
	while (1)
		read_command(&minishell, &data);
}
