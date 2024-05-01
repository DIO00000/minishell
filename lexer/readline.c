/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:43:42 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/01 12:49:41 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*read_line(t_minishell *minishell)
{
	char	*line;

	if (isatty(0))
	{
		minishell->input = readline(minishell->trm_prompt);
		if (!minishell->input || !ft_strncmp(*ft_split(minishell->input, ' '), "exit", 5))
			(printf("exit\n"), free(minishell->input), exit(1));
	}
	else
	{
		line = get_next_line(0);
		minishell->input = ft_strtrim(line, "\n");
		free(line);
	}
	minishell->trimed_cmd = ft_strtrim(minishell->input, SPACES);
	if (minishell->input == NULL)
		return (NULL);
	return ((void *)1);
}