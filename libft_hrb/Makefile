# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 16:05:15 by oelharbi          #+#    #+#              #
#    Updated: 2024/05/16 12:46:52 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

CC = cc

BONUS = ft_lstadd_front_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o ft_lstadd_back_bonus.o\
		ft_lstnew_bonus.o ft_lstdelone_bonus.o ft_lstclear_bonus.o ft_lstmap_bonus.o ft_lstiter_bonus.o\

OBJ = ft_isascii.o ft_memcmp.o ft_strchr.o ft_strncmp.o\
	ft_bzero.o ft_isdigit.o ft_memcpy.o ft_strlcat.o ft_strrchr.o\
	ft_isalnum.o ft_isprint.o ft_memmove.o ft_strlcpy.o ft_tolower.o\
	ft_isalpha.o ft_memchr.o ft_memset.o ft_strlen.o ft_toupper.o ft_strnstr.o\
	ft_atoi.o ft_calloc.o ft_strdup.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o\
	ft_putnbr_fd.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o\
	ft_striteri.o\

HEADER = libft.h

all : $(NAME)

$(NAME) : $(OBJ) 
	@ar rcs $@ $^
	
bonus : $(BONUS) $(OBJ)
	@ar rcs $(NAME) $^
	
%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $<

clean :
	@rm -rf $(OBJ) $(BONUS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean re