# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 22:20:54 by hbettal           #+#    #+#              #
#    Updated: 2024/04/18 22:43:15 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINEDIR		=		$(shell brew --prefix readline)
SRC = ft_split.c minishell.c utilities.c setup.c here_doc.c signals.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -L$(READLINEDIR)/lib -lreadline
