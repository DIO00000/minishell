/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 12:45:16 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	classing(t_parser **expand)
{
	t_parser	*tmp;

	(*expand)->class = COMMAND;
	tmp = *expand;
	while (tmp)
	{
		if (!tmp->class)
			tmp->class = ARGUMENT;
		tmp = tmp->next;
	}
	expand = &tmp;
}

int	is_space(char *str)
{
	while (str && *str)
	{
		if (ft_iswhitespace(*str))
			return (1);
		str++;
	}
	return (0);
}

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
	char			**spl;
	t_parser		*expand;
	int				i;
	int				count;

	expand = NULL;
	i = -1;
	help.exp_counter = expansion_counter(current->string);
	if (help.exp_counter)
	{
		count = count_quote(current->string);
		if (count > 0)
			current->string = remove_quotes(&current->string, count);
	}
	while (help.exp_counter--)
	{
		if (current->class != LIM)
			ex_set(mini, &current->string, &help, data);
		if (is_space(current->string))
		{
			count = 0;
			count = count_quote(current->string);
			if (count > 0)
				current->string = remove_quotes(&current->string, count);
			spl = ft_split(current->string, SPACES);
			if (!spl)
				return ;
			while (spl[++i])
				lstadd_back(&expand, lstnew(spl[i]));
			classing(&expand);
			if (mini->lst->string != current->string)
				current = lstadd_middle(mini->lst, expand, current->string);
			else
				lstadd_front(&mini->lst, expand, current->string);
		}
	}
}
