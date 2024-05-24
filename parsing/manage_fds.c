/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:35:05 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/24 00:23:34 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_fds(t_minishell *mini)
{
	int	index;

	index = 0;
	while (index < mini->list_size)
	{
		if (!mini->final_cmd[index].redirection_in)
		{
			if (index == 0)
				mini->final_cmd[index].in_fd = 0;
			else
				mini->final_cmd[index].in_fd = TUBE;
		}
		if (!mini->final_cmd[index].redirection_out)
		{
			if (index == mini->list_size - 1)
				mini->final_cmd[index].out_fd = 1;
			else
				mini->final_cmd[index].out_fd = TUBE;
		}
		open_fds(mini, index);
		index++;
	}
}
