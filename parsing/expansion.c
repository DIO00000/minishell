/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/24 06:21:45 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_set(t_minishell *mini, char **str, t_exp_helper *help)
{
	t_list	*tmp;

	tmp = NULL;
	help->start = ft_start((*str));
	if (!help->start || expansion_error((*str)[help->start]))
		return ;
	if ((*str)[help->start] == '?')
		return (exit_number(mini, &(*str), help->start));
	help->end = ft_end((*str), help->start);
	help->exp_name = ft_substr((*str), help->start, help->start - help->end);
	if (!help->exp_name)
		ft_exit(mini, NULL, NULL, 12);
	// tmp = var_finder(help->exp_name, &data);
	help->exp_env = tmp->env;
	free(help->exp_name);
	// (*str) = var_value();
	if (!(*str))
		ft_exit(mini, NULL, NULL, 12);
}

void	parameter_expansion(t_minishell *mini, t_parser *current)
{
	t_exp_helper	help;

	help.exp_counter = expansion_counter(current->string);
	while (help.exp_counter--)
	{
		if (current->class != LIM)
			ex_set(mini, &current->string, &help);
	}
}
