/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:17 by oelharbi          #+#    #+#             */
/*   Updated: 2024/04/19 12:16:53 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	*lstlast(t_type *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst -> next;
	return (lst);
}

void	lstadd_back(t_type **lst, t_type *new)
{
	t_type	*last;

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

t_type	*lstnew(char *str, int type)
{
	t_type	*head;

	head = malloc(sizeof(t_type));
	if (!head)
		write(1, "error\n", 6), exit(1);
	head->string = str;
	head->type = type;
	head->next = NULL;
	return (head);
}
