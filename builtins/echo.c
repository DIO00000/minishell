/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:06:12 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/03 19:26:15 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_echo(char *word)
{
	char	**split;
	char	*tmp;
	int		i;
	
	i = -1;
	tmp = NULL;
	split = ft_split(word, "\"");
	tmp = NULL;
	while (split[++i])
	{
		word = ft_strjoin(tmp, split[i]);
		free(tmp);
		tmp = word;
	}
	free_handler(split);
	return (word);
}

void	echo_build(char	**cmd, t_minishell *mini)
{
	int		i;
	int		j;
	bool	n;

	(1) && (i = 1, n = false, mini->exit_status = 0);
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 1;
		while (cmd[i][j] && cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			i++;
		else
			break ;
	}
	(i == 1) && (n = true);
	while (cmd[1] && cmd[i])
	{
		cmd[i] = parse_echo(cmd[i]);
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	(n == true) && (printf("\n"));
}
