/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:46:01 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/16 22:45:07 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		(free(strings[i]), i++);
	free(strings);
}

void	print_error(char *var, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}


// void	cleanup(t_minishell *mini, int exit_status)
// {
// 	(void)mini;
// 	(void)exit_status;

// 	if (mini->table)
// 	{
// 		free_table(mini);
// 		mini->table = NULL;
// 	}
// 	// if (mini->lst)
// 	// 	ft_lstclear(&mini->lst);
// 	if (mini->cmd)
// 	{
// 		free(mini->cmd);
// 		mini->cmd = NULL;
// 	}
// 	if (mini->pids)
// 	{
// 		free(mini->pids);
// 		mini->pids = NULL;
// 	}
// 	if (exit_status != EXIT_SUCCESS && mini->new_env)
// 		free_strings(mini->new_env);
// 	return ;
// }

void	ft_exit(t_minishell *mini, char *cmd, char *str, int ext)
{
	(void)mini;
	struct stat	file;

	if (ext == 13)
	{	
		ext = 126;
	}
	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
		print_error(cmd, "is a directory");
	else if (str || ext)
		print_error(cmd, str);
	// if (mini)
	// 	cleanup(mini, ext);
	if (ext)
		exit(ext);
}