/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:54:13 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/17 00:06:37 by oelharbi         ###   ########.fr       */
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
	while (lst->next != NULL)
		lst = lst -> next;
	return (lst);
}

void	lstadd_back(t_parser **lst, t_parser *new)
{
	t_parser	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
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