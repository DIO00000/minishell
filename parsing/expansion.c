/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/18 14:47:28 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parameter_expansion(t_minishell *mini, char *current)
{
	(void)mini;
	int	exp_counter;
	// int	index;

	exp_counter = expansion_counter(current);
	printf("exp_ counetr ===> %d\n", exp_counter);
}