# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 15:53:11 by inaranjo          #+#    #+#              #
#    Updated: 2023/07/06 15:45:48 by inaranjo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = libft/

SRC =	main.c \
		init_prompt.c \
		expand_var.c \
		manage_lst.c \
		parsing_cmds.c \
		parsing_prompt.c \
		parsing_tokens.c \
		ramasse_miette.c \
		setup_builtin.c \
		setup_env.c \
		setup_err.c \
		setup_pipes.c \
		setup_redir.c \
		sig_handler.c \
		split_simulator.c \
		useless_token.c \
		utils_cmd.c \
		utils_expand.c \
		utils_pipex.c \
		utils_redir.c \
		utils.c \
		


CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all : subsystems $(NAME)

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o} -I$(HOME)/.brew/opt/readline/include
	@printf $(UP)$(CUT)

subsystems :
	@echo $(B)
	make -C $(LIBFT_PATH) all

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(SRC)]...$(X)
	@echo $(G)Finished [$(SRC)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -I$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib -lreadline
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJ)
	@echo $(R)Removed [$(OBJ)]$(X)


fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re
