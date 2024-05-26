/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:45:00 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/26 19:33:21 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	indexer(t_list **data)
{
	t_list	*tmp;
	t_list	*cur;
	int		index;

	tmp = *data;
	index = 0;
	while (tmp)
	{
		index = 0;
		cur = *data;
		while (cur)
		{
			if (ft_strncmp(tmp->env, cur->env, LONG_MAX) > 0)
				index++;
			cur = cur->next;
		}
		tmp->index = index;
		tmp = tmp->next;
	}
}

t_list	*var_finder(char *var, t_list **data)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, ft_strjoin(var, "="), ft_strlen(var) + 1))
			return (tmp);
		else if (!ft_strncmp(tmp->env, var, ft_strlen(tmp->env)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_variable(char *var, t_list **data, char **sps, int i)
{
	t_list	*tmp;

	tmp = *data;
	if (!sps[1])
		if (!var_finder(sps[0], data))
			(ft_lstadd_back(data, ft_lstnew(var)));
	if (sps[0][i - 1] != '+' && sps[1])
	{
		if (!var_finder(sps[0], data))
			(ft_lstadd_back(data, ft_lstnew(var)));
		else
		{
			tmp = var_finder(sps[0], data);
			tmp->env = var;
		}
	}
	else if (sps[0][i - 1] == '+' && sps[1])
	{
		tmp = var_finder(*ft_split(sps[0], "+"), data);
		if (ft_strchr(tmp->env, '='))
			tmp->env = ft_strjoin(tmp->env, sps[1]);
		else
			tmp->env = ft_strjoin_three(tmp->env, "=", sps[1]);
	}
}

void	creat_var(char **var, t_list **data, int i)
{
	char	**sps;

	while (var[++i])
	{
		sps = ft_split(var[i], "=");
		(add_variable(var[i], data, sps, ft_strlen(sps[0])), indexer(data));
		free_handler(sps);
	}
}

void	export_build(char **var, t_list **data)
{
	int		i;
	t_list	*tmp;

	if (!export_parse(var))
		return ;
	tmp = *data;
	i = -1;
	if (!var[1])
	{
		while (++i < ft_lstsize(*data))
		{
			tmp = *data;
			while (tmp)
			{
				if (tmp->index == i && ft_strncmp(tmp->env, "PATH=/usr", 9))
					printf("declare -x %s\n", tmp->env);
				tmp = tmp->next;
			}
		}
	}
	creat_var(var, data, 0);
}
