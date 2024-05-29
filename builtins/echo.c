/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:06:12 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/29 06:15:42 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_build(char	**cmd, t_minishell *mini)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		while (cmd[1][i] && cmd[1][i] == 'n')
			i++;
		if (cmd[1][i] != 'n' && cmd[1][i] != '\0')
			i = 1;
		else
			(1) && (i = 2, n = true);
	}
	while (cmd[1] && cmd[i])
		printf("%s ", cmd[i++]);
	if (n == false)
		printf("\n");
	mini->exit_status = 0;
}
