/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:41:37 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/01 12:54:55 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fd(t_minishell *mini, t_pex *pex)
{
	if (mini->final_cmd[pex->i].in_fd == TUBE)
	{
		if (dup2(pex->end[0], 0) == -1)
			fds_closer(pex->end);
	}
	else
	{
		if (dup2(mini->final_cmd[pex->i].in_fd, 0) == -1)
			return fds_closer(pex->end);
	}		
	if (mini->final_cmd[pex->i].out_fd == TUBE && mini->list_size > 1)
	{
		if (dup2(pex->end[1], 1) == -1)
			return fds_closer(pex->end);
	}
	else
	{		
		if (dup2(mini->final_cmd[pex->i].out_fd, 1) == -1)
			return fds_closer(pex->end);
	}
}
