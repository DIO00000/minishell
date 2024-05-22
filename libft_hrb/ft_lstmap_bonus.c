/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:23 by oelharbi          #+#    #+#             */
/*   Updated: 2023/12/01 15:49:15 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;
	void	*data;

	if (!lst)
		return (NULL);
	node = NULL;
	while (lst)
	{
		data = f(lst->content);
		tmp = ft_lstnew(data);
		if (!tmp)
		{
			del(data);
			ft_lstclear(&node, del);
			return (NULL);
		}
		ft_lstadd_back(&node, tmp);
		lst = lst->next;
	}
	return (node);
}
