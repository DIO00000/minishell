/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:14:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/21 17:31:19 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_dir(char *dir, t_minishell *m)
{
	char	*curr_dir;
	if (!access(dir, F_OK) && access(dir, R_OK))
	{
		(printf("cd: permission denied: %s\n", dir), m->exit_status = 1);
		return (0);
	}
	if (dir[0] == '-' && !dir[1])
	{
		curr_dir = getcwd(NULL, 0);
		if (chdir(m->last_dir) == -1)
			(printf("cd: No such file or directory\n"), m->exit_status = 1);
		else
            (free(m->last_dir), m->last_dir = curr_dir);
		m->curr_dir = getcwd(NULL, 0);
		printf("%s\n", m->curr_dir);
		return (0);
	}
	else if (dir[0] == '~' && !dir[1])
	{
		m->last_dir = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			(printf("cd: No such file or directory\n"), m->exit_status = 1);
		return (0);
	}
	return (1);
}

void    cd_build(char **dir, t_minishell *m)
{
	if (!dir[1])
	{
		m->last_dir = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			(printf("cd: No such file or directory\n"), m->exit_status = 1);
		m->curr_dir = getcwd(NULL, 0);
		return ;
	}
	if (!cd_dir(dir[1], m))
		return ;
	else 
	{
		m->last_dir = getcwd(NULL, 0);
		if (chdir(dir[1]) == -1)
			(printf("cd: No such file or directory\n"), m->exit_status = 1);
		m->curr_dir = getcwd(NULL, 0);
		return ;
	}
}
