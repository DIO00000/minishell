/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:24:39 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/29 10:17:40 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_build(t_minishell *mini, char **status)
{
	int	i;

	i = -1;
	if (status[1])
	{
		if (status[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			mini->exit_status = 1;
			return ;
		}
		while (status[1][++i])
		{
			if (!ft_isdigit(status[1][i]))
			{
				printf("exit\nminishell: exit: %s:\
 numeric argument required\n", status[1]);
				exit(255);
			}
		}
		(printf("exit\n"), exit(ft_atoi(status[1])));
	}
	exit(mini->exit_status);
}
