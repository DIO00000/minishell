/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:49:43 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/25 14:03:12 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_minishell *mini, t_list *data)
{
	int	i;

	i = -1;
	if (!mini->cmd[0])
		return (1);
	while (mini->cmd[++i])
		lstadd_back(&mini->lst, lstnew(mini->cmd[i]));
	(classification(mini, data), systax_error(mini->lst));
	if (!mini->lst)
		return (1);
	if (!struct_cmd(mini))
		ft_exit(mini, NULL, NULL, 12);
		// exit (0);
	// if (mini->syntax)
	// 	return (mini->syntax = 0, ft_exit(mini, NULL, NULL, 0), 1);
	// if (mini->exit_status == 7)
	// 	return (mini->exit_status = 1, 1);
	// int o =0;
	// while (mini->final_cmd[0].cmd[o])
	// {
	// 	printf("FLAGS ==> [%s] i ==>[%d]\n", mini->final_cmd[0].cmd[o], o);
	// 	o++;
	// }
	single_command(mini, &data);
	signal(SIGQUIT, sig_quit);
	// excute(mini);
	return (0);
}
