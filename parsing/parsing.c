/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:49:43 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/20 13:32:39 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_minishell *mini)
{
	int	i;

	i = -1;
	if (!mini->cmd[0])
		return ;
	while (mini->cmd[++i])
		lstadd_back(&mini->lst, lstnew(mini->cmd[i]));
	classification(mini);
	while (mini->lst)
	{
		printf("THE SRTING => [%s]\n", mini->lst->string);
		mini->lst = mini->lst->next;
	}
}
