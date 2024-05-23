/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:47:15 by hbettal           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 20:40:19 by oelharbi         ###   ########.fr       */
=======
/*   Updated: 2024/05/20 23:23:13 by hbettal          ###   ########.fr       */
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*empty_env(t_list *data, t_minishell *mini)
{
	ft_lstadd_back(&data, ft_lstnew(mini->defult_path));
	ft_lstadd_back(&data, ft_lstnew("OLDPWD"));
	ft_lstadd_back(&data, ft_lstnew(ft_strjoin("PWD=", mini->curr_dir)));
	ft_lstadd_back(&data, ft_lstnew("SHLVL=1"));
	ft_lstadd_back(&data, ft_lstnew("_=/usr/bin/env"));
	return (data);
}

t_list	*fill_env(char **origin_env, t_list *data, t_minishell *mini)
{
	int		i;
	t_list	*tmp;
	char	*ctmp;

	i = -1;
	if (!origin_env[0])
		data = empty_env(data, mini);
	else
	{
		while (origin_env[++i])
			ft_lstadd_back(&data, ft_lstnew(origin_env[i]));
	}
	tmp = data;
	ctmp = tmp->env;
	while (tmp->next)
	{
		ctmp = ft_strjoin_three(ctmp, " ",tmp->next->env);
		tmp = tmp->next;
	}
	mini->new_env = ft_split(ctmp, " ");
	free(ctmp);
	indexer(&data);
	return (data);
}

void	env_build(t_list *data, char *cmd)
{
	if (cmd)
	{
		printf("env: %s: No such file or directory\n", cmd);
		return ;
	}
	if (!ft_strncmp(data->env, "PATH=", 5))
		data = data->next;
	while (data)
	{
		if (ft_strchr(data->env, '='))
			printf("%s\n", data->env);
		data = data->next;
	}
}

void	ft_shlvl(t_list *data, t_minishell *m)
{
	t_list	*tmp;
	int		level;
	char	**var;
	char	*ctmp;
	char	*str;
	int		i;

	i = 0;
	tmp = var_finder("SHLVL", &data);
<<<<<<< HEAD
	var = ft_split(tmp->env, "=");
=======
	var = ft_split(tmp->env, '=');
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
	level = ft_atoi(var[1]) + 1;
	tmp->env = ft_strjoin("SHLVL=", ft_itoa(level));
	tmp = data;
	ctmp = tmp->env;
	while (tmp->next)
	{
		str = ft_strjoin_three(ctmp, " ",tmp->next->env);
		if (i)
			free(ctmp);
		ctmp = str;
		tmp = tmp->next;
		i++;
	}
<<<<<<< HEAD
	m->new_env = ft_split(ctmp, " ");
=======
	m->new_env = ft_split(ctmp, ' ');
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
	(free_handler(var), free(ctmp));
}

void	ft_pwd(t_list	*data, t_minishell *m)
{
	t_list	*tmp;
	
	tmp = var_finder("PWD", &data);
	tmp->env = ft_strjoin("PWD=", m->curr_dir);
	tmp = var_finder("OLDPWD", &data);
	tmp->env = ft_strjoin("OLDPWD=", m->last_dir);
}
