/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:14:13 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/25 22:58:38 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_dir(char *dir, t_minishell *mini)
{
	char	*curr_dir;
	if (!access(dir, F_OK) && access(dir, R_OK))
	{
		printf("cd: permission denied: %s\n", dir);
		return (0);
	}
	if (dir[0] == '-' && !dir[1])
	{
		curr_dir = getcwd(NULL, 0);
		if (chdir(mini->last_dir) == -1)
			write(2, "cd: No such file or directory\n", 30);
		else
            (free(mini->last_dir), mini->last_dir = curr_dir);
		printf("%s\n", getcwd(NULL, 0));
		return (0);
	}
	else if (dir[0] == '~' && !dir[1])
	{
		mini->last_dir = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			write(2, "cd: No such file or directory\n", 30);
		return (0);
	}
	return (1);
}

void    cd_build(char **dir, t_minishell *mini)
{
	if (!dir[1])
	{
		mini->last_dir = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			write(2, "cd: No such file or directory\n", 30);
		return ;
	}
	if (!cd_dir(dir[1], mini))
		return ;
	else 
	{
		mini->last_dir = getcwd(NULL, 0);
		if (chdir(dir[1]) == -1)
			write(2, "cd: No such file or directory\n", 30);
		mini->curr_dir = getcwd(NULL, 0);
		return ;
	}
}
