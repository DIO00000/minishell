/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:43:42 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/02 23:18:16 by hbettal          ###   ########.fr       */
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
