/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:45:00 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/26 22:50:27 by hbettal          ###   ########.fr       */
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

void	add_variable(char **var, t_list **data, char **sps, int i)
{
	t_list	*tmp;
	char	*n_var;

	tmp = *data;
	n_var = NULL;
	// if (!unvalid_var(var))
	// 	;
	while(sps[0][i])
		i++;
	if (!sps[1])
	{
		n_var = ft_strjoin(var[1], "=''");
		(ft_lstadd_back(data, ft_lstnew(n_var)), indexer(data));
	}
	else if (sps[0][i - 1] != '+')
		(ft_lstadd_back(data, ft_lstnew(var[1])), indexer(data));
}

void	export_build(char **var, t_list **data)
{
	int		i;
	int		size;
	char	**sps;
	t_list	*tmp;

	tmp = *data;
	sps = ft_split(var[1], '=');
	i = -1;
	size = ft_lstsize(*data);
	if (!var[1])
	{
		while (++i < size)
		{
			tmp = *data;
			while (tmp)
			{
				(tmp->index == i) && (printf("declare -x %s\n", tmp->env));
				tmp = tmp->next;
			}
		}
	}
	else
	(i = 0, add_variable(var, data, sps, i));
}
