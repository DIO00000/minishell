/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:36:44 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/20 11:44:39 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operator(t_parse_state *state, t_parser *current)
{
	if (*current->string == '|')
	{
		current->class = PIPE;
		*state = START;
	}
	else if (*current->string == '<')
	{
		handle_redirection(current, REDIN);
		*state = IN_FILE;
		if (current->class == HERDOC && current->next)
		{
			current->class = LIM;
			*state = IN_HEREDOC;
		}
	}
	else if (*current->string == '>')
	{
		handle_redirection(current, REDOUT);
		*state = IN_FILE;
	}
}

void	some_thing_else(t_parse_state *state, t_parser *current)
{
	if (*state == START)
	{
		current->class = COMMAND;
		*state = IN_COMMAND;
	}
	else if (*state == IN_COMMAND)
	{
		current->class = ARGUMENT;
		*state = IN_ARG;
	}
	else
	{
		current->class = FILE;
		*state = IN_COMMAND;
	}
}

void	classification(t_minishell *mini)
{
	t_parser		*current;
	t_parse_state	state;
	int				count_quotes;

	current = mini->lst;
	state = START;
	count_quotes = 0;
	while (current)
	{
		operator(&state, current);
		parameter_expansion(mini, current);
		count_quotes = count_quote(current->string);
		if (count_quotes > 0)
		{
			current->string = remove_quotes(&current->string, count_quotes);
			if (!current->string)
				ft_exit(mini, NULL, NULL, 12);
		}
		if (count_quotes == -1)
			current->class = ERROR;
		if (!current->class)
			some_thing_else(&state, current);
		current = current->next;
	}
}
