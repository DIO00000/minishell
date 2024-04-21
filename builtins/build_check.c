/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/21 17:05:00 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    build_check(char *cmd, t_minishell *mini)
{
	int	q;

	q = 0;
	if (!ft_strncmp(cmd, "cd ", 3))
		(cd_build(cmd, mini), q = 1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		(pwd_build(cmd), q = 1);
	return (q);
}