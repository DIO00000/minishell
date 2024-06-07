/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:49:43 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/07 11:52:36 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_minishell *mini, t_list **data)
{
	int		i;

	i = -1;
	if (!mini->cmd[0])
		return (1);
	while (mini->cmd[++i])
		lstadd_back(&mini->lst, lstnew(mini->cmd[i]));
	(classification(mini, *data), systax_error(mini->lst));
	t_parser *a = mini->lst;
	while (a)
	{
		printf("=>> %s\n", a->string);
		a = a->next;
	}
	if (!mini->lst)
		return (1);
	if (!struct_cmd(mini, *data))
		ft_exit(mini, NULL, NULL, 12);
	if (mini->syntax)
		return (mini->syntax = 0, ft_exit(mini, NULL, NULL, 0), 1);
	if (mini->exit_status == 7)
		return (mini->exit_status = 1, 1);
	signal(SIGQUIT, sig_quit);
	single_command(mini, data);
	return (0);
}
