# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 22:20:54 by hbettal           #+#    #+#              #
#    Updated: 2024/04/20 20:53:39 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
SRC = ft_split.c minishell.c utilities.c setup.c here_doc.c signals.c parsing/exit.c special_cases.c redirection.c builtins/build_check.c builtins/cd/cd.c prompt/*.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(READLINE_INC) $(READLINE_LIB) -o $(NAME) 


clean:
	rm -f $(NAME)