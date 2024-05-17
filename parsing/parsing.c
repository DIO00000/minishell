/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:49:43 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/17 00:30:19 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_minishell *mini)
{
	int	i;

	i = -1;
	if (!mini->cmd)
		return ;
	while (mini->cmd[++i])
		lstadd_back(&mini->lst, lstnew(mini->cmd[i]));
	// int j = 0;
	// while (mini->lst)
	// {
	// 	printf("The string [%d] => %s\n", j, mini->lst->string);
	// 	mini->lst = mini->lst->next;
	// }
}