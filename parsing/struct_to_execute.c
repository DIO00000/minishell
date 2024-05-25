/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:30:47 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/25 13:57:37 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	struct_cmd(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->list_size = lstsize(mini->lst);
	mini->final_cmd = malloc(sizeof(t_final_st) * mini->list_size);
	if (!mini->final_cmd)
		return (0);
	while (i < mini->list_size)
		mini->final_cmd[i++].cmd = NULL;
	i = 0;
	while (i < mini->list_size)
	{
		mini->final_cmd[i].redirection_in = NULL;
		mini->final_cmd[i].redirection_out = NULL;
		if (!set_cmd_line(mini, i))
			return (0);
		if (!open_files(mini, i))
			return (1);
		i++;
		
	}
	manage_fds(mini);
	return (1);
}