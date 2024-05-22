# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 22:20:54 by hbettal           #+#    #+#              #
#    Updated: 2024/05/20 07:11:33 by hbettal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
SRC =  utilities/ft_split.c minishell.c utilities/utilities.c excution/setup.c redirect/here_doc.c \
		signals/signals.c parsing/exit.c utilities/special_cases.c builtins/pwd.c builtins/echo.c \
		redirect/redirection.c builtins/build_check.c builtins/cd.c prompt/prompt.c builtins/env.c \
		utilities/list.c utilities/ft_strtrim.c builtins/export.c lexer/readline.c \
		builtins/unset.c lexer/get_next_line.c lexer/get_next_line_utils.c \
		lexer/lexer.c utilities/numbers_utlis.c lexer/lexer_utils.c \

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(READLINE_INC) $(READLINE_LIB) -o $(NAME) 

clean:
	rm -f $(NAME)
