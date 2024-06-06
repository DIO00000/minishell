/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:33:53 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 18:27:16 by oelharbi         ###   ########.fr       */
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
	if (ft_strchr(var, '='))
		return(ft_strchr(var, '=') + 1);
	return (NULL);
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
}

void	check_spaces(t_parser *current, t_minishell *mini)
{
	int 			count;
	t_parser		*expand;
	char			**spl;
	int				i;

	expand = NULL;
	i = -1;
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

void	parameter_expansion(t_minishell *mini, t_parser *current, t_list *data)
{
	t_exp_helper	help;
	int				i;
	int				count;

	i = -1;
	count = 0;
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
			check_spaces(current, mini);
	}
}
//export +=
