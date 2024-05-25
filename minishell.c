/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:02:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/25 12:24:52 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*mini_init(t_minishell *m, t_list *data, char **env)
{
	(1) && (m->input = NULL, m->exit_status = 0, m->env_status = 0);
	(1) && (m->pids = NULL, m->cmd = NULL, m->final_cmd = NULL);
	(1) && (m->new_env = NULL, m->trm_prompt = NULL, m->last_dir = NULL);
	(1) && (m->curr_dir = getcwd(NULL, 0), m->username = getenv("USER"));
	(1) && (m->lst = NULL, m->defult_path = malloc(90 * sizeof(char)));
	m->defult_path = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
	/usr/local/munki:/Library/Apple/usr/bin";
	data = fill_env(env, data, m);
	m->cmd_path = "./minishell";
	ft_shlvl(data, m);
	return (data);
}

void	read_line(t_minishell *mini)
{
	char	*line;
	char	**c_exit;
	
	mini->input = readline(mini->trm_prompt);
	printf("%s", mini->input);
	if (mini->input && ft_strncmp(mini->input, "\n", 1))
		add_history(mini->input);
	// mini->input = readline(GREEN_ARROW X);
	if (!(c_exit = ft_split(mini->input, " ")))
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
		prompt_custom(&mini);
		read_line(&mini);
		lexer(&mini);
		parsing(&mini, data);
		ft_exit(&mini, NULL, NULL, 0);
	}
}
