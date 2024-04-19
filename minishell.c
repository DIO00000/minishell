/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:39:52 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/18 22:44:54 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals(int sig) 
{
	(void)sig;

    printf("\n\033[1;33m➜ \033[1;34m minishell ♛ \033[0;m");
} 

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	handler();
	// signal(SIGINT, handle_signals);
	read_command(env);
}