/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:41:37 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/20 15:56:51 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_red(char **token) 
{
	int		fd;
	
	fd = open(token[1], O_RDONLY);
	if (dup2(fd, 0) == -1)
		exit(1);
}

char	**last_red(char *line)
{
	int		fd;
	char	**token;
	
	//cat > minishell
	token = split_token(line);
	fd = open(token[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd, 1) == -1)
			exit(1);
	return (ft_split(token[0], ' '));
}
