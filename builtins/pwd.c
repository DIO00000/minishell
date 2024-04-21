/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 00:05:10 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/22 00:32:06 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_build(char *pwd, t_minishell *mini)
{
	int	i;
	
	i = 3;
	while (pwd[i] == ' ')
		i++;
	if (pwd[i])
	{
		write(2, "pwd: too many arguments\n", 24);
		return ;
	}
	printf("%s\n", mini->curr_dir);
}
