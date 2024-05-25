/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:54:13 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/25 13:34:23 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*lstnew(void *content)
{
	t_parser	*head;

	head = malloc(sizeof(t_parser));
	if (head == NULL)
		return (NULL);
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
		// (free(current->string), free(current));
		current = next;
	}
	*lst = NULL;
}

int	count_quote(char *str)
{
	char	current_quote;
	int		count;

	count = 0;
	while (*str)
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
	new_str = malloc(((ft_strlen(*str) - count_quotes) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while ((*str)[j])
	{
		if ((*str)[j] != '\'' && (*str)[j] != '\"')
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