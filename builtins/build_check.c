/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 20:39:48 by oelharbi         ###   ########.fr       */
=======
/*   Updated: 2024/05/20 22:04:50 by hbettal          ###   ########.fr       */
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    build_check(char *cmd, t_minishell *mini, t_list **data)
{
	int		q;
	char	**flags;

	q = 0;
	if (!(flags = ft_split(cmd, " ")))
		return (0);
	if (!ft_strncmp(flags[0], "cd", 3))
		(cd_build(flags, mini), ft_pwd(*data, mini), q = 1);
	else if (!ft_strncmp(flags[0], "pwd", 4))
		(pwd_build(cmd, mini), q = 1);
	// else if (!ft_strncmp(flags[0], "echo", 5))
	// 	(echo_build(cmd), q = 1);
	else if (!ft_strncmp(flags[0], "env", 4))
		(env_build(*data,flags[1]), q = 1);
	else if (!ft_strncmp(flags[0], "export", 7))
		(export_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "unset", 6))
	(unset_build(flags, data), q = 1);
	return (q);
}
