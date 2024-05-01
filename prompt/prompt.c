/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:37:21 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/01 12:17:52 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    prompt_custom(t_minishell *minishell)
{
	char    *username;
	char    *final;
	char    *n_arrow;
	char    *cur_dir;
	char    *dir;
	
	if (minishell->trm_prompt != NULL)
		free(minishell->trm_prompt);
	cur_dir = get_dir(minishell);
	if (minishell->cmd_excuted == 1)
		username = ft_strjoin_h(GREEN_ARROW, minishell->username);
	else
		username = ft_strjoin_h(RED_ARROW, minishell->username);
	dir = ft_strjoin_h(SPC, cur_dir);
	n_arrow = ft_strjoin_h(username, dir);
	final = ft_strjoin_h(n_arrow, X);
	free(username);
	free(dir);
	free(n_arrow);
	free(cur_dir);
	minishell->trm_prompt = final;
	minishell->cmd_excuted = 1;
}

char    *get_dir(t_minishell *minishell)
{
	(void)minishell;
	int i;
	char *pwd;
	char **split;
	char *dir;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	if (ft_strncmp(pwd, "/", ft_strlen(pwd)) == 0)
		dir = ft_strdup("/");
	// if (ft_strncmp(pwd + 7, minishell->username, ft_strlen(pwd + 7)) == 0) 
	// 	dir = ft_strdup("~");
	else
	{
		split = ft_split(pwd, '/');
		while (split[i])
			i++;
		dir = ft_strdup(split[--i]);
		free_handler(split);
	}
	return (dir);
}
