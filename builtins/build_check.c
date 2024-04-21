/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/22 00:10:15 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    build_check(char *cmd, t_minishell *mini)
{
	int		q;
	char	**flags;

	q = 0;
	if (!(flags = ft_split(cmd, ' ')))
		return (0);
	if (!ft_strncmp(flags[0], "cd", 3))
		(cd_build(cmd, mini), q = 1);
	else if (!ft_strncmp(flags[0], "pwd", 4))
		(pwd_build(cmd), q = 1);
	else if (!ft_strncmp(flags[0], "echo", 5))
		(echo_build(cmd), q = 1);
	return (q);
}