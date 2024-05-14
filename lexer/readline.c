/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:43:42 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/05 21:35:06 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*read_line(t_minishell *mini)
{
	char	*line;
	char	**c_exit;
	
	mini->input = readline(mini->trm_prompt);
	if (!(c_exit = ft_split(mini->input, ' ')))
		(printf("exit\n"), exit(mini->exit_status));
	if (isatty(0))
	{
		if (!mini->input || !ft_strncmp(c_exit[0], "exit", 5))
		{
			if (!c_exit[1])
				(printf("exit\n"), free(mini->input), exit(mini->exit_status));
			else
				(printf("exit\n"), free(mini->input), exit(ft_atoi(c_exit[1])));
		}
	}
	else
	{
		line = get_next_line(0);
		mini->input = ft_strtrim(line, "\n");
		free(line);
	}
	mini->trimed_cmd = ft_strtrim(mini->input, SPACES);
	return ((void *)1);
}
