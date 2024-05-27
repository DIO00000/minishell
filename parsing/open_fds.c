/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:11 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/27 02:20:04 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_outfd(t_parser *curr, t_parser *redirecyion_out)
{
	int	fd;

	fd = -9000;
	if (curr->class == REDOUT)
	{
		fd = open(curr->next->string, O_RDWR | O_TRUNC | O_CREAT, 0644);
		printf("if ==> [%d]\n", fd);
		if (fd == -1)
			fd = open(curr->next->string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (curr->class == APPEND)
	{
		fd = open(curr->next->string, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			fd = open(curr->next->string, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
	{
		print_error(curr->next->string, NULL);
		return (-1);
	}
	if (curr == redirecyion_out)
		return (fd);
	close(fd);
	return (-9000);
}

int	open_infd(t_parser *curr, t_parser *redirecyion_in)
{
	int	fd;

	if (!curr->next->string[0])
	{
		print_error(NULL, "ambiguous redirect");
		return (-1);
	}
	fd = open(curr->next->string, O_RDONLY);
	if (fd == -1)
	{
		print_error(curr->next->string, NULL);
		return (-1);
	}
	if (curr == redirecyion_in)
		return (fd);
	close(fd);
	return (-1337);
}

void	open_fds(t_minishell *mini, int i)
{
	t_parser	*curr;

	curr = get_pipe(mini->lst, i);
	while (curr && curr->class != PIPE)
	{
		if (curr->class == REDIN)
		{
			(mini->final_cmd[i].in_fd > 2) && (close(mini->final_cmd[i].in_fd));
			mini->final_cmd[i].in_fd = \
			open_infd(curr, mini->final_cmd[i].redirection_in);
		}
		if (curr->class == REDOUT || curr->class == APPEND)
		{
			if (mini->final_cmd[i].out_fd > 2)
				close(mini->final_cmd[i].out_fd);
			mini->final_cmd[i].out_fd = \
			open_outfd(curr, mini->final_cmd[i].redirection_out);
		}
		if (mini->final_cmd[i].in_fd == -1 || mini->final_cmd[i].out_fd == -1)
		{
			mini->exit_status = 1;
			return ;
		}
		curr = curr->next;
	}
}

void	close_fds(t_minishell *mini)
{
	int i;

	i = 0;
	while (i < mini->list_size)
	{
		if (mini->final_cmd[i].out_fd > 2)
			close(mini->final_cmd[i].out_fd);
		if (mini->final_cmd[i].out_fd > 2)
			close(mini->final_cmd[i].in_fd);
		i++;
	}
	close(3);
}