/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:45:00 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/26 01:52:55 by hbettal          ###   ########.fr       */
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

void	export_build(char **var, t_list **data)
{
	int		i;
	int		size;
	t_list	*tmp;

	tmp = *data;
	i = -1;
	size = ft_lstsize(*data);
	if (!var[1])
	{
		while (++i < size)
		{
			tmp = *data;
			while (tmp)
			{
				if (tmp->index == i)
					printf("declare -x %s\n", tmp->env);
				tmp = tmp->next;
			}
		}
	}
	else if (ft_strrchr(var[1], '='))
		(ft_lstadd_back(data, ft_lstnew(var[1])), indexer(data));
}
