/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_execute_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:34:46 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 12:53:53 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_parser *lst)
{
	int	pipe_line;

	pipe_line = 1;
	while (lst)
	{
		if (lst->class == PIPE)
			pipe_line++;
		lst = lst->next;
	}
	return (pipe_line);
}

int	set_cmd_line(t_minishell *mini, int i)
{
	t_parser	*curr;
	int			cmd_size;
	int			index;

	curr = get_pipe(mini->lst, i);
	cmd_size = get_cmd_size(mini, curr, i);
	mini->final_cmd[i].cmd = malloc(sizeof(char *) * (cmd_size + 1));
	if (!mini->final_cmd[i].cmd)
		return (0);
	index = 0;
	while (index < i)
	{
		if (curr->class == ARGUMENT || curr->class == COMMAND)
			mini->final_cmd[i].cmd[index++] = curr->string;
		curr = curr->next;
	}
	mini->final_cmd[i].cmd[index] = NULL;
	return (1);
}

int	get_cmd_size(t_minishell *mini, t_parser *curr, int i)
{
	int	index;
	int	cmd_size;

	index = 0;
	cmd_size = 0;
	while (curr && curr->class != PIPE)
	{
		mini->final_cmd[i].in_fd = -2;
		mini->final_cmd[i].out_fd = -2;
		if (curr->class == ARGUMENT || curr->class == COMMAND)
			cmd_size++;
		if (curr->class == HERDOC || curr->class == REDIN)
			mini->final_cmd[i].redirection_in = curr;
		else if (curr->class == APPEND || curr->class == REDOUT)
			mini->final_cmd[i].redirection_out = curr;
		curr = curr->next;
	}
	return (cmd_size);
}

t_parser	*get_pipe(t_parser *lst, int i)
{
	int	index;

	index = 0;
	if (i == 0)
		return (lst);
	while (lst && index < i)
	{
		if (lst->class == PIPE)
			index++;
		lst = lst->next;
	}
	return (lst);
}

int	open_files(t_minishell *mini, int i)
{
	t_parser	*curr;
	int			her_fd;

	her_fd = 0;
	curr = get_pipe(mini->lst, i);
	while (curr && curr->class != PIPE)
	{
		if (curr->class == HERDOC)
		{
			// her_fd = ft_here_doc(mini, curr->next); //Hamza
			if (mini->env_status == 7)
				return (close(her_fd), ft_close_fds(mini), 0);
			if (curr == mini->final_cmd[i].redirection_in)
				mini->final_cmd[i].in_fd = her_fd;
			else
				close (her_fd);
		}
		if (curr->class == ERROR)
		{
			mini->exit_status = 258;
			mini->syntax = 1;
			return (ft_close_fds(mini), 0);
		}
		curr = curr->next;
	}
	return (1);
}

void	ft_close_fds(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->list_size)
	{
		if (mini->final_cmd[i].in_fd > 2)
			close(mini->final_cmd[i].in_fd);
		if (mini->final_cmd[i].out_fd > 2)
			close(mini->final_cmd[i].out_fd);
		i++;
	}
}
