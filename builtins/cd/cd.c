/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:14:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/20 21:23:28 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    cd_build(char *cmd)
{
	char    **dir;

	dir = ft_split(cmd, ' ');
	if (!dir)
		return ;
	if (dir[1] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			write(2, "No such file or directory", 25);
		return ;
	}
	if (chdir(dir[1]) == -1)
		write(2, "No such file or directory", 25);
}