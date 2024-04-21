/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 00:05:10 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/21 10:04:45 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_build(char *pwd)
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
	printf("%s\n", getcwd(NULL, 0));
}