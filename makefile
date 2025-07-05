# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 01:24:17 by mez-zahi          #+#    #+#              #
#    Updated: 2025/06/25 12:03:55 by idahhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

# les dossiers
SRC = src
INCLUDE = include
COMMAND = command
SIGNAL = signal
PREPAR = prepare
EXPAND = expand
PARSING = parsing
LEXER = lexer
LEXER_2 = lexer_2
HERDOC = herdoc
SYNTAX = syntaxe_error
UTILS = utils
EXECUTOR = executor
BUILTINS = builtins
LIBFT_UTILS = libft_utils

HANDL_ERROR = handl_error

READLINE=$(shell brew --prefix readline)/lib
READLINE1=$(shell brew --prefix readline)/include
#les fils 
SRCS = main.c \
		$(SRC)/$(UTILS)/ft_space.c \
		$(SRC)/$(UTILS)/init_env.c \
		$(SRC)/$(UTILS)/free.c \
		$(SRC)/$(UTILS)/command_path.c \
		$(SRC)/$(UTILS)/print_error.c \
		$(SRC)/$(UTILS)/utils1.c \
		$(SRC)/$(UTILS)/utils2.c \
		$(SRC)/$(UTILS)/utils3.c \
		$(SRC)/$(LEXER)/lexer_1.c \
		$(SRC)/$(LEXER)/lexer_2.c \
		$(SRC)/$(LEXER)/lexer_3.c \
		$(SRC)/$(LEXER)/lexer_4.c \
		$(SRC)/$(LEXER)/lexer_5.c \
		$(SRC)/$(LEXER)/lexer_6.c \
		$(SRC)/$(HERDOC)/ft_herdoc_1.c \
		$(SRC)/$(HERDOC)/ft_herdoc_2.c \
		$(SRC)/$(SYNTAX)/verify_cmd_1.c \
		$(SRC)/$(SYNTAX)/verify_cmd_2.c \
		$(SRC)/$(EXPAND)/expand_var_1.c   \
		$(SRC)/$(EXPAND)/expand_var_2.c \
		$(SRC)/$(EXPAND)/expand_var_3.c \
		$(SRC)/$(EXPAND)/expand_var_4.c \
		$(SRC)/$(EXPAND)/expand_var_5.c \
		$(SRC)/$(EXPAND)/expand_var_6.c \
		$(SRC)/$(PREPAR)/ft_concate_tkn.c \
		$(SRC)/$(PREPAR)/remove_red.c\
		$(SRC)/$(PREPAR)/preparer_cmd_1.c\
		$(SRC)/$(PREPAR)/preparer_cmd_2.c\
		$(SRC)/$(PREPAR)/preparer_cmd_3.c\
		$(SRC)/$(PREPAR)/preparer_cmd_4.c\
		$(SRC)/$(SIGNAL)/signal.c \
		$(SRC)/$(EXECUTOR)/exec_main.c \
		$(SRC)/$(EXECUTOR)/exec_external.c \
		$(SRC)/$(EXECUTOR)/exec_pipe.c \
		$(SRC)/$(EXECUTOR)/redirection.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/cd_builtin.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/echo_builtin.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/exit_builtin.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/export_builtin1.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/export_builtin2.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/unset_builtin.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/exec_builtin.c \
		$(SRC)/$(EXECUTOR)/$(BUILTINS)/env_builtin.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strlen.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strdup.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_substr.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strtrim.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strjoin.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strcmp.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_isalnum.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_itoa.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_atol.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_malloc.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_putstr_fd.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_split.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strchr.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strncmp.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strlcpy.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strcat.c \
		$(SRC)/$(UTILS)/$(LIBFT_UTILS)/ft_strcpy.c \
# object 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -L $(READLINE) -I $(READLINE1) -o $(NAME)
	@echo "\033[0;32m Minishell compiled\033[0m"

%.o: %.c include/minishell.h
	@printf "\033[0;32m Compiling minishell: \033[0;33m$<\033[0m\r"
	@$(CC) $(CFLAGS) -I $(READLINE1) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "\033[0;32m Cleaned\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;32m Fcleaned\033[0m"

re: fclean all
