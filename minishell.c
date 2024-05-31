/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:02:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/31 05:49:17 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*mini_init(t_minishell *m, t_list *data, char **env)
{
	(1) && (m->input = NULL, m->exit_status = 0, m->env_status = 0);
	(1) && (m->pids = NULL, m->cmd = NULL, m->final_cmd = NULL);
	(1) && (m->new_env = NULL, m->trm_prompt = NULL, m->last_dir = NULL);
	(1) && (m->curr_dir = getcwd(NULL, 0), m->username = getenv("USER"));
	(1) && (m->lst = NULL, m->syntax = 0, m->cmd_path = "./minishell");
	m->defult_path = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:\
/usr/bin:.");
	data = fill_env(env, data, m);
	free(env);
	ft_shlvl(data, m);
	return (data);
}

void	read_line(t_minishell *mini)
{
	char	*line;

	mini->input = readline(mini->trm_prompt);
	if ((mini->input) && ft_strncmp(mini->input, "\n", 2))
		add_history(mini->input);
	if (!mini->input)
		(printf("exit\n"), exit(mini->exit_status));
	if (isatty(0))
	{
		if (!mini->input)
			(printf("exit\n"), free(mini->input), exit(mini->exit_status));
	}
	else
	{
		line = get_next_line(0);
		mini->input = ft_strtrim(line, "\n");
		free(line);
	}
}

void f()
{
	system("leaks minishell");
}

char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

int	main(int ac, char **av, char **env)
{
	char		**my_env;
	t_minishell	mini;
	t_list		*data;
	// atexit(f);

	data = NULL;
	my_env = copy_env(env);
	((void)ac, (void)av);
	if (!isatty(0))
		return (print_error(NULL, "this input is not a tty"), 1);
	data = mini_init(&mini, data, my_env);
	while (1)
	{
		signals(&mini.term);
		prompt_custom(&mini);
		read_line(&mini);
		lexer(&mini);
		parsing(&mini, data);
		ft_exit(&mini, NULL, NULL, 0);
	}
}
