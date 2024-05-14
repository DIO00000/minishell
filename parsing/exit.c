/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:09:20 by oelharbi          #+#    #+#             */
/*   Updated: 2024/04/19 15:12:32 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_error(char *str, char *msg)
{
    if (str)
        write(2, str, ft_strlen(str));
    else if (msg)
        write(2, msg, ft_strlen(msg));
    else
        write(2, strerror(errno), ft_strlen(strerror(errno)));
    write(2, "\n", 1);
}
