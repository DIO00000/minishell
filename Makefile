# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:05:04 by oelharbi          #+#    #+#              #
#    Updated: 2024/05/22 13:11:04 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

READLINE_INC = -I$(shell brew --prefix readline)/include

READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

NAME = minishell

LIBFT = ./libft/libft.a

HEADER = minishell.h ./libft/libft.h

OBJ = minishell.o signals.o parsing/lexer.o parsing/exit.o parsing/lexer_utils.o parsing/prompt.o parsing/parsing.o parsing/parsing_utils.o parsing/classification.o parsing/expansion.o parsing/expansion_utils.o parsing/syntax_error.o parsing/struct_to_execute_utils.o parsing/struct_to_execute.o parsing/garbage_collector.o

all: $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

$(NAME) : $(OBJ) $(LIBFT) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ)  $(READLINE_LIB)  -o $(NAME)

$(LIBFT) :
	@echo "\033[1;33mBuilding LIBFT...\033[0m"
	@make -C ./libft
	@echo "\033[1;33mBuilding Minishell...\033[0m"

# ./mandatory/%.o : ./mandatory/%.c $(HEADER)
# 	@echo "\033[0;34mCompiling $< .\033[0;m"
# 	@sleep 0.2
# 	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

%.o : %.c $(HEADER)
	@echo "\033[0;34mCompiling $< .\033[0;m"
	@sleep 0.2
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@



clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"
	@sleep 0.2
	@echo "\033[0;31mRemoving object files.\033[0;m"
	@sleep 0.2
	@rm -f $(OBJ)
	@make clean -C ./libft
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving program.\033[0;m"
	@echo "\033[1;32mDONE ✅\033[0;m"
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all 

.PHONY: clean