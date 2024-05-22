/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:01 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/21 17:38:06 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_check(char *command, t_list *data, int end[])
{
	int		i;
	char	*cmnd;
	char	*path;
	char	**paths;

	if (access(command, F_OK) != -1)
		return (command);
	i = -1;
	paths = ft_split(where_path(data), ':');
	if (!paths)
		exit(1);
	cmnd = ft_strjoin("/", command);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmnd);
		if (access(path, F_OK) != -1)
			return (free_handler(paths), free(cmnd), path);
		free(path);
	}
	(free_handler(paths), free(cmnd), fds_closer(end));
	write(2, "command not found\n", 19);
	exit (127);
}

void	middle_commands(t_pex *pex, char *line, t_list **data, t_minishell *m)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(line, ' ');
		if (dup2(pex->input, 0) < 0)
			(write (2, "dup2 failed", 11), exit(1));
		close(pex->input);
		path = path_check(commands[0], *data, pex->end);
		if (!commands || !path)
			(fds_closer(pex->end), exit(1));
		if (dup2(pex->end[1], 1) == -1)
			return (fds_closer(pex->end), exit(1));
		fds_closer(pex->end);
		execve(path, commands, m->new_env);
		exit(1);
	}
}

void	last_cmd(int end[], char *line, t_list **data, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(line, ' ');
		if (ft_strrchr(line, '>'))
			commands = last_red(line);
		dup2(end[0], 0);
		path = path_check(commands[0], *data, end);
		if (!commands || !path)
			exit(1);
		fds_closer(end);
		execve(path, commands, mini->new_env);
		exit(1);
	}
}

void	first_cmd(t_list **data, t_pex *pex, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		commands = ft_split(pex->split_line[0], ' ');
		if (!commands)
			(fds_closer(pex->end), exit(1));
		if (!ft_strncmp(commands[0], "<", 2) && commands[1] && commands[2])
		{
			path_check(commands[2], *data, pex->end);
			commands = first_red(commands);
		}
		path = path_check(commands[pex->i - 1], *data, pex->end);
		if (!path)
			(fds_closer(pex->end), exit(1));
		if ((pex->lines > 1 && pex->i == 1) || (pex->lines == 1 && pex->i == 2))
			if (dup2(pex->end[1], 1) == -1)
				return (fds_closer(pex->end), exit(1));
		fds_closer(pex->end);
		(execve(path, commands, mini->new_env), exit(1));
	}
}

void	more_commands(t_pex *pex, t_list **data, t_minishell *mini)
{
	int	status;

	if (pex->lines > 1)
	{
		pex->input = pex->end[0];
		while (pex->split_line[pex->i + 1])
		{
			if (pipe(pex->end) == -1)
				(write(2, "pipe failed", 11), exit(1));
			middle_commands(pex, pex->split_line[pex->i], data, mini);
			close(pex->end[1]);
			close(pex->input);
			pex->input = pex->end[0];
			pex->i++;
		}
		last_cmd(pex->end, pex->split_line[pex->i], data, mini);
	}
	(free_handler(pex->split_line), fds_closer(pex->end));
	while (!wait(&status))
		;
	mini->exit_status = (status >> 8) & 0xFF;
}

void	single_command(char *line, t_minishell *mini, t_list **data)
{
	t_pex	pex;

	pex.i = 1;
	pex.split_line = ft_split(line, '|');
	if (build_check(pex.split_line[0], mini, data))
		return ;
	pex.lines = count_words(line, '|');
	if (pipe(pex.end) == -1)
		(write(2, "Error\n", 7), exit(1));
	if (!ft_strncmp(line, "<<", 2))
		(ft_here_doc(&pex, pex.split_line[0]), close(pex.end[1]));
	else
		(first_cmd(data, &pex, mini), close(pex.end[1]));
	more_commands(&pex, data, mini);
	close(pex.end[0]);
}

void	read_command(t_minishell *mini, t_list **data)
{
	while (1)
	{
		signals(&mini->term);
		prompt_custom(mini);
		if (read_line(mini) == NULL)
			break ;
		lexer(mini);
		single_command(mini->input, mini, data);
		add_history(mini->input);
	}
}
