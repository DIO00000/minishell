/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/01 12:13:51 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expansion_error(char c)
{
	if (c == '_' || c == '?')
		return (0);
	else if (!ft_isalpha(c))
		return (1);
	return (0);
}

char	*var_value(char	*var)
{
	char	*value;
	char	**tmp;

	tmp = ft_split(var, "=");
	value = tmp[1];
	free(tmp[0]);
	free(tmp);
	return (value);
}

void	ex_set(t_minishell *mini, char **str, t_exp_helper *help, t_list *data)
{
	t_list	*tmp;

	help->start = ft_start((*str));
	if (!help->start || expansion_error((*str)[help->start]))
		return ;
	if ((*str)[help->start] == '?')
		return (exit_number(mini, &(*str), help->start));
	help->end = ft_end((*str), help->start);
	help->exp_name = ft_substr((*str), help->start, help->end - help->start);
	if (!help->exp_name)
		ft_exit(mini, NULL, NULL, 12);
	tmp = var_finder(help->exp_name, &data);
	if (!tmp)
	{
		(*str) = NULL;
		return ;
	}
	help->exp_env = tmp->env;
	free(help->exp_name);
	(*str) = remove_str(str, var_value(help->exp_env), help->start, \
	help->end - help->start);
	if (!(*str))
		ft_exit(mini, NULL, NULL, 12);
}

void	parameter_expansion(t_minishell *mini, t_parser *current, t_list *data)
{
	t_exp_helper	help;

	help.exp_counter = expansion_counter(current->string);
	while (help.exp_counter--)
	{
		if (current->class != LIM)
			ex_set(mini, &current->string, &help, data);
	}
}
