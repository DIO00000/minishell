
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 04:28:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/20 23:13:05 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*minishell_init(t_minishell *m, t_list *data, char **env)
{
	m->curr_dir = getcwd(NULL, 0);
	m->last_dir = NULL;
	m->defult_path = malloc(90 * sizeof(char));
	m->defult_path = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki:/Library/Apple/usr/bin";
	data = fill_env(env, data, m);
	m->pids = NULL;
	m->env_status = 0;
	m->syntax = 0;
	m->cmd_excuted = 1;
	m->trm_prompt = NULL;
	m->username = getenv("USER");
	m->cmd_path = "./minishell";
	m->trimed_cmd = NULL;
	m->exit_status = 0;
	ft_shlvl(data, m);
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
