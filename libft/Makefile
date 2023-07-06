# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 11:52:25 by malleman          #+#    #+#              #
#    Updated: 2023/07/06 12:03:39 by inaranjo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
	  	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	  	ft_strlcat.c ft_strchr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
	  	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	  	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	  	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_isprint.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c basic_function.c \
		ft_printf.c nb_hexa.c ptr_hexa.c unsigned.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

.SILENT:

.c.o:
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@printf $(UP)$(CUT)

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}
	@echo $(G)Finished creating [$(NAME)]$(X)

all: ${NAME}

clean:
	rm -f ${OBJS}
	@echo $(R)Removed [$(OBJS)]$(X)

fclean: clean
	rm -f ${NAME}
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re