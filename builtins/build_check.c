/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/26 01:40:49 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    build_check(char *cmd, t_minishell *mini, t_list **data)
{
	int		q;
	char	**flags;

	q = 0;
	if (!(flags = ft_split(cmd, ' ')))
		return (0);
	if (!ft_strncmp(flags[0], "cd", 3))
		(cd_build(flags, mini), q = 1);
	else if (!ft_strncmp(flags[0], "pwd", 4))
		(pwd_build(cmd, mini), q = 1);
	else if (!ft_strncmp(flags[0], "echo", 5))
		(echo_build(cmd), q = 1);
	else if (!ft_strncmp(flags[0], "env", 4))
		(env_build(*data, mini, flags[1]), q = 1);
	else if (!ft_strncmp(flags[0], "export", 7))
		(export_build(flags, data), q = 1);
	return (q);
}
