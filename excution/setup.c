/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:01 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/21 10:39:39 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_check(char *command, char **env, int end[])
{
	int		i;
	char	*cmnd;
	char	*path;
	char	**paths;

	if (access(command, F_OK) != -1)
		return (command);
	i = 0;
	paths = ft_split(where_path(env), ':');
	if (!paths)
		exit(1);
	cmnd = ft_strjoin("/", command);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmnd);
		if (access(path, F_OK) != -1)
			return (free_handler(paths), free(cmnd), path);
		free(path);
		i++;
	}
	free_handler(paths);
	free(cmnd);
	fds_closer(end);
	write(2, "command not found\n", 19);
	return (NULL);
}

void	middle_commands(int end[], char *line, char **env, int input)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(line, ' ');
		if (dup2(input, 0) < 0)
			(write (2, "dup2 failed", 11), exit(1));
		close(input);
		path = path_check(commands[0], env, end);
		if (!commands || !path)
			(fds_closer(end), exit(1));
		if (dup2(end[1], 1) == -1)
			return (fds_closer(end), exit(1));
		fds_closer(end);
		execve(path, commands, env);
		exit(1);
	}
}

void	last_cmd(int end[], char *line, char **env)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(line, ' ');
		if (ft_strrchr(line, '>'))
			commands = last_red(line);
		dup2(end[0], 0);
		path = path_check(commands[0], env, end);
		if (!commands || !path)
			exit(1);
		fds_closer(end);
		execve(path, commands, env);
		exit(1);
	}
}

void	first_cmd(int end[], char **s_line, char **env, int lines, t_pex *pex)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(s_line[0], ' ');
		if (!ft_strncmp(commands[0], "<", 2))
			(first_red(commands), pex->i = 2);
		path = path_check(commands[pex->i - 1], env, end);
		if (!commands || !path)
			(fds_closer(end), exit(1));
		if ((lines > 1 && pex->i == 1 ) || (lines == 1 && pex->i == 2))
			if (dup2(end[1], 1) == -1)
				return (fds_closer(end), exit(1));
		fds_closer(end);
		(execve(path, commands, env), exit(1));
	}
}

void	more_commands(t_pex pex, char **env)
{
	if (pex.lines > 1)
	{
		pex.input = pex.end[0];
		while (pex.split_line[pex.i + 1])
		{
			if (pipe(pex.end) == -1)
				(write(2, "pipe failed", 11), exit(1));
			(middle_commands(pex.end, pex.split_line[pex.i], env, pex.input), close(pex.end[1]));
			pex.input = pex.end[0]; //end[1] == 3 --> input == 3
			pex.i++;
		}
		last_cmd(pex.end, pex.split_line[pex.i],env);
	}
	fds_closer(pex.end);
	while (wait(NULL) == 0)
		;
}

void	single_command(char *line, char **env, t_minishell *mini)
{
	t_pex	pex;

	pex.i = 1;
	pex.split_line = ft_split(line, '|');
	if (build_check(pex.split_line[0], mini))
			return ;
	// special_cases(pex.split_line, env);
	pex.lines = count_words(line, '|');
	if (pipe(pex.end) == -1)
		(write(2, "Error\n", 7), exit(1));
	(first_cmd(pex.end, pex.split_line, env, pex.lines, &pex), close(pex.end[1]));
	// if (!ft_strncmp(line, "<<", 2))
	// 	(ft_here_doc(pex.end), close(pex.end[1]), pex.i++);
	// else
	more_commands(pex, env);
}

void	read_command(t_minishell *mini, char **env)
{
	char	*line;

	while (1)
	{
		prompt_custom(mini);
		line = readline(mini->trm_prompt);
		if (!line || !ft_strncmp(line, "exit", 5))
			(free(line), exit(1));
		add_history(line);
		single_command(line, env, mini);
	}
}

