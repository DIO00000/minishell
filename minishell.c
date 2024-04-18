/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:39:52 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/18 22:31:13 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals(int sig) 
{ 
    printf("\n>> ");
} 

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	signal(SIGINT, handle_signals);
	read_command(env);
}