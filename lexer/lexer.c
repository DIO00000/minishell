/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:00:49 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/08 15:38:21 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_minishell *minishell)
{
	if (ft_strlen(minishell->trimed_cmd) == 0 || isempty_line(minishell) == 1)
		return (0);
	return (1);
}

int	isempty_line(t_minishell *minishell)
{
	int	end;
	
	end = ft_strlen(minishell->trimed_cmd) - 1;
	if (minishell->trimed_cmd[0] == '~' && ft_strlen(minishell->trimed_cmd) == 1)
	{
		printf("%s: %s%s: %s\n", "minishell", "/Users/", minishell->username, "is a directory");
		return (1);
	}
	if ((minishell->trimed_cmd[0] == '>' && minishell->trimed_cmd[1] == '>' && minishell->trimed_cmd[2] == '>') || (minishell->trimed_cmd[0] == '<' && minishell->trimed_cmd[1] == '<' && minishell->trimed_cmd[2] == '<'))
	{
		if (minishell->trimed_cmd[0] == '>')
			printf("%s: %s\n", "minishell", "syntax error near unexpected token `>'");
		else
			printf("%s: %s\n", "minishell", "syntax error near unexpected token `newline'");
		return (1);
	}
	if (minishell->trimed_cmd[0] == '"' && minishell->trimed_cmd[1] == '"' && ft_strlen(minishell->trimed_cmd) == 2)
	{
		printf("%s: : %s\n", "minishell", "command not found");
		minishell->cmd_excuted = 0;
		return (1);
	}
	if (minishell->trimed_cmd[0] == '|' || minishell->trimed_cmd[end] == '|')
	{
		printf("%s: %s\n", "minishell", "syntax error near unexpected token `|'");
		return (1);
	}
	return (0);
}
