/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:54:13 by oelharbi          #+#    #+#             */
/*   Updated: 2024/06/06 18:27:33 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*lstnew(void *content)
{
	t_parser	*head;

	head = zyalloc(sizeof(t_parser), 'a', true);
	head->string = content;
	head->next = NULL;
	return (head);
}

t_parser	*lstlast(t_parser *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	new->class = 0;
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
}

void	lstclear(t_parser **lst)
{
	t_parser	*current;
	t_parser	*next;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		current = next;
	}
	*lst = NULL;
}

int	count_quote(char *str)
{
	char	current_quote;
	int		count;

	current_quote = '\0';
	count = 0;
	while (str && *str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (current_quote == '\0')
				(1 == 1) && (current_quote = *str, count++);
			else if (*str == current_quote)
				(1 == 1) && (current_quote = '\0', count++);
		}
		str++;
	}
	if (current_quote != '\0')
		return (-1);
	return (count);
}

char	*remove_quotes(char **str, int count_quotes)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = zyalloc(((ft_strlen(*str) - count_quotes) + 1) \
	* sizeof(char), 'a', true);
	while ((*str)[j])
	{
		if ((*str)[j] != '\"')
			new_str[i++] = (*str)[j];
		j++;
	}
	new_str[i] = '\0';
	return (free(*str), *str = NULL, new_str);
}

void	handle_redirection(t_parser *current, int class)
{
	if (class == REDIN)
	{
		if (!current->string[1])
			current->class = REDIN;
		else if (current->string[1] == '<' && !current->string[2])
			current->class = HERDOC;
		else
			current->class = ERROR;
	}
	else
	{
		if (!current->string[1])
			current->class = REDOUT;
		else if (current->string[1] == '>' && !current->string[2])
			current->class = APPEND;
		else
			current->class = ERROR;
	}
}

t_parser	*lstadd_middle(t_parser *lst, t_parser *new, char *str)
{
	t_parser	*prev;
	t_parser	*curr;
	t_parser	*last_of_new;

	if (!lst || !new)
		return (lst);
	if (lst->string == str && !lst->next)
		return (new);
	prev = NULL;
	curr = lst;
	last_of_new = new;
	while (curr && curr->next && curr->string != str)
	{
		prev = curr;
		curr = curr->next;
	}
	last_of_new = lstlast(new);
	last_of_new->next = curr->next;
	if (prev)
		prev->next = new;
	else
		lst = new;
	return (lst);
}

void	lstadd_front(t_parser **lst, t_parser *new, char *str)
{
	t_parser	*last_of_new;

	if (!(*lst) || !new)
		return ;
	last_of_new = new;
	if ((*lst)->string == str && (*lst)->next)
	{
		last_of_new = lstlast(new);
		last_of_new->next = (*lst)->next;
	}
	*lst = new;
}

// void	ft_lstadd_back(t_list_parse **lst, char *str)
// {
// 	t_list_parse	*temp;
// 	t_list_parse	*new;

// 	new = ft_lstnew(str);
// 	new->flag = 0;
// 	temp = *lst;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = *lst;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new;
// }