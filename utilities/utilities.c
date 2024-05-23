/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:28:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/23 22:30:56 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*where_path(t_list *data)
{
	int		j;
	char	*name;

	name = "PATH=";
	while (data->env)
	{
		j = 0;
		while (data->env[j] && data->env[j] == name[j])
		{
			if (!name[j + 1])
				return (data->env + 5);
			j++;
		}
		data = data->next;
	}
	return (NULL);
}

