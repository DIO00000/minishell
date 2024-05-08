/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:41:37 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/08 16:07:56 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*valid_cmd(char *command, t_list *data, int end[])
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
	return (NULL);
}

// void	no_pipe_case(char *token)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	if (token[2] && token[2])
// 	{
// 		while (!valid_cmd())
// 		{
// 			/* code */
// 		}
		
// 	}
// }

char	**first_red(char **token) 
{
	int		fd;
	int		i;
	char	*commands;
	
	//< Makefile cat |
	i = 2;
	while (token[i])
		commands = ft_strjoin(commands, token[i++]);
	fd = open(token[1], O_RDONLY);
	if (dup2(fd, 0) == -1)
		exit(1);
	return(ft_split(commands, ' '));
}

char	**last_red(char *line)
{
	int		fd;
	int		i;
	char	**token;
	char	**commands;
	
	// | cat > minishell
	i = 0;
	token = ft_split(line, '>');
	commands = ft_split(token[0], ' ');
	while (commands[i])
		i++;
	fd = open(*ft_split(token[1], ' '), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd, 1) == -1)
			exit(1);
	free_handler(token);
	return (commands);
}
