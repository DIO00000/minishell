/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:43:05 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/18 14:44:29 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expansion_counter(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '$')
			count++;
		str++;
	}
	return (count);
}
