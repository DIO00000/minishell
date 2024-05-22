/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:59:39 by oelharbi          #+#    #+#             */
/*   Updated: 2023/12/01 15:29:55 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;
	size_t	check;

	check = count * size;
	if (size != 0 && check / size != count)
		return (NULL);
	m = malloc(count * size);
	if (m == NULL)
		return (NULL);
	ft_bzero(m, (count * size));
	return (m);
}
