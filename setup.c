/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:01 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/18 10:33:33 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	write(2, "command not found", 18);
	return (NULL);
}

void	middle_commands(int end[], char *line, char **env, int i, int input)
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
	int		fd;
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		dup2(end[0], 0);
		commands = ft_split(line, ' ');
		path = path_check(commands[0], env, end);
		if (!commands || !path)
			exit(1);
		fds_closer(end);
		execve(path, commands, env);
		exit(1);
	}
}

void	first_cmd(int end[], char *line, char **env, int lines)
{
	int		fd;
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(line, ' ');
		path = path_check(commands[0], env, end);
		if (!commands || !path)
			(fds_closer(end), exit(1));
		if (lines > 1)
			if (dup2(end[1], 1) == -1)
				return (fds_closer(end), exit(1));
		fds_closer(end);
		(execve(path, commands, env), exit(1));
	}
}

void	command_handler(char *line, char **env)
{
	t_pex	pex;

	pex.i = 1;
	pex.split_line = ft_split(line, '|');
	// special_cases(pex.split_line, env);
	pex.lines = count_words(line, '|');
		if (pipe(pex.end) == -1)
			(write(2, "Error\n", 7), exit(1));
		(first_cmd(pex.end, pex.split_line[0], env, pex.lines), close(pex.end[1]));
	// if (!ft_strncmp(line, "<<", 2))
	// 	(ft_here_doc(pex.end), close(pex.end[1]), pex.i++);
	// else
	if (pex.lines > 1)
	{		pex.input = pex.end[0];
		while (pex.split_line[pex.i + 1])
		{
			if (pipe(pex.end) == -1)
				(write(2, "pipe failed", 11), exit(1));
			(middle_commands(pex.end, pex.split_line[pex.i], env, pex.i, pex.input), close(pex.end[1]));
			pex.input = pex.end[0]; //end[1] == 3 --> input == 3
			pex.i++;
		}
		last_cmd(pex.end, pex.split_line[pex.i],env);
	}
	fds_closer(pex.end);
	while (wait(NULL) == 0)
		;
}

void	read_command(char **env)
{
	char	*line;

	while (1)
	{
		line = readline(">> ");
		if (!line)
			return (free(line));
		add_history(line);
		command_handler(line, env);
	}
}