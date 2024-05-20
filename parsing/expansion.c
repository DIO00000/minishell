/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/20 13:15:21 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expansion_set(t_minishell *mini, char **string, t_exp_helper *help)
{
	help->start = ft_start((*string));
	if (!help->start || expansion_error((*string)[help->start]))
	{
		printf("Name ==> %d\n", help->start);
		return ;
	}
	if ((*string)[help->start] == '?')
	{
		exit_number(mini, &(*string), help->start);
		return ;
	}
	help->end = ft_end((*string), help->start);
	help->exp_name = ft_substr((*string), help->start, help->start - help->end);
	if (!help->exp_name)
		ft_exit(mini, NULL, NULL, 12);
	// help->exp_env = get_env(mini->new_env, help->exp_name);
	free(help->exp_name);
	// (*string) = remove_str(string, help->exp_env, help->start, help->end - help->start);
	// if (!(*string))
	// 	ft_exit(mini, NULL, NULL, 12);
}

void	parameter_expansion(t_minishell *mini, t_parser *current)
{
	t_exp_helper	help;

	help.exp_counter = expansion_counter(current->string);
	while (help.exp_counter--)
	{
		if (current->class != LIM)
		{
			expansion_set(mini, &current->string, &help);
		}
	}
}
