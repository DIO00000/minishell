/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:13:01 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/26 21:08:57 by hbettal          ###   ########.fr       */
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
	paths = ft_split(where_path(data), ":");
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
	printf("minishell: %s: command not found", command);
	exit (127);
}

void	middle_commands(t_pex *pex, t_list **data, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		check_fd(mini, pex);
		if (build_check(mini, data, pex))
			exit(1);
		else
		{
			commands = mini->final_cmd[pex->i + 1].cmd;
			if (dup2(pex->input, 0) < 0)
				(write (2, "dup2 failed", 11), exit(1));
			close(pex->input);
			path = path_check(commands[0], *data, pex->end);
			if (!commands || !path)
				(fds_closer(pex->end), exit(1));
			fds_closer(pex->end);
		}
		execve(path, commands, mini->new_env);
		exit(1);
	}
}

pid_t	last_cmd(t_pex *pex, t_list **data, t_minishell *mini)
{
	char	*path;
	char	**commands;
	pid_t	id;

	commands = NULL;
	id = fork();
	if (id == 0)
	{
		pex->i++;
		check_fd(mini, pex);
		// if (dup2(pex->end[0], 0) == -1)
		// 	(fds_closer(pex->end), exit(1));
		if (build_check(mini, data, pex))
			exit(1);
		else
		{
			commands = mini->final_cmd[pex->i].cmd;
			path = path_check(commands[0], *data, pex->end);
			if (!commands || !path)
				exit(1);
			fds_closer(pex->end);
		}
		//write(2, commands[0], ft_strlen(*commands));
		execve(path, commands, mini->new_env);
		exit(1);
	}
	return (id);
}

void	first_cmd(t_list **data, t_pex *pex, t_minishell *mini)
{
	char	*path;
	char	**commands;

	if (fork() == 0)
	{
		check_fd(mini, pex);
		if (build_check(mini, data, pex))
		{
			fds_closer(pex->end);
			exit(mini->exit_status);
		}
		else
		{
			commands = mini->final_cmd[0].cmd;
			if (!commands)
				(fds_closer(pex->end), exit(1));
			path = path_check(commands[pex->i], *data, pex->end);
			if (!path)
				(fds_closer(pex->end), exit(1));
			fds_closer(pex->end);
		}
		(execve(path, commands, mini->new_env), exit(1));
	}
}

void	more_commands(t_pex *pex, t_list **data, t_minishell *mini)
{
	int		status;
	pid_t	id;

	id = 0;
	if (mini->list_size > 1)
	{
		pex->input = pex->end[0];
		while (pex->i + 2 < mini->list_size)
		{
			if (pipe(pex->end) == -1)
				(write(2, "pipe failed\n", 12), exit(1));
			middle_commands(pex, data, mini);
			close(pex->end[1]);
			close(pex->input);
			pex->input = pex->end[0];
			pex->i++;
		}
		id = last_cmd(pex, data, mini);
	}
	fds_closer(pex->end);
	// wait last cmd in args before wait all other cmds
	//wait()
	waitpid(id, &status, 0);
	while (wait(NULL) != -1)
		;
	mini->exit_status = (status >> 8) & 0xFF;
}

void	single_command(t_minishell *mini, t_list **data)
{
	t_pex	pex;

	pex.i = 0;
	mini->exit_status = 0;
	if (mini->list_size == 1)
		if (build_check(mini, data, &pex))
			return ;
	pex.lines = mini->list_size;
	if (pipe(pex.end) == -1)
		(write(2, "Error\n", 6), exit(1));
	(first_cmd(data, &pex, mini), close(pex.end[1]));
	more_commands(&pex, data, mini);
	// if (mini->final_cmd[(&pex)->i].out_fd != 1)
	// 	close(mini->final_cmd[(&pex)->i].out_fd);
	// if (mini->final_cmd[(&pex)->i].out_fd != 0)
	// 	close(mini->final_cmd[(&pex)->i].in_fd);
	close(pex.end[0]);
}

// void	read_command(t_minishell *mini, t_list **data)
// {
// 	while (1)
// 	{
// 		signals(&mini->term);
// 		prompt_custom(mini);
// 		if (read_line(mini) == NULL)
// 			break ;
// 		lexer(mini);
// 		single_command(mini->input, mini, data);
// 		add_history(mini->input);
// 	}
// }
