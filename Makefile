# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 22:20:54 by hbettal           #+#    #+#              #
#    Updated: 2024/04/19 15:20:27 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
SRC = ft_split.c minishell.c utilities.c setup.c here_doc.c signals.c parsing/exit.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(READLINE_INC) $(READLINE_LIB) -o $(NAME) 
