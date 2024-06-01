/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:06:12 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/01 11:01:28 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_build(char	**cmd, t_minishell *mini)
{
	int		i;
	int		j;
	bool	n;

	i = 1;
	n = false;
	while (cmd[i] && !ft_strncmp(cmd[1], "-n", 2))
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
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	(n == true) && (printf("\n"));
	mini->exit_status = 0;
}
