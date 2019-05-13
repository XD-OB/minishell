# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 14:29:38 by obelouch          #+#    #+#              #
#    Updated: 2019/05/12 23:57:11 by obelouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
EOC = \033[1;0m

NAME = minishell

B_PATH = ./src/builtins/

BUILTINS = echo

EXEC = $(addprefix $(B_PATH), $(BUILTINS))

LIB = -L ./libft -lft

MINISHELL = ft_split_quote ft_split_invquote main prompt tools cmdsplit cmd_user\
			cd env setenv unsetenv tools_env\

SRC = $(addprefix src/, $(addsuffix .c, $(MINISHELL)))

OBJ = $(addsuffix .o, $(MINISHELL))

FLAGS = 

CMD_BUILT = gcc -o $(B_PATH)echo $(FLAGS) $(LIB) $(B_PATH)echo.c $(B_PATH)print_echo.c && \
			gcc -o $(B_PATH)setenv $(FLAGS) $(LIB) $(B_PATH)setenv.c $(B_PATH)setenv_tools.c\

all : $(NAME)

$(NAME) :
		@make -C ./libft re && make -C ./libft clean
		@gcc -c $(FLAGS) -I ./ $(SRC)
		@$(CMD_BUILT)
		@gcc -o $(NAME) $(OBJ) $(LIB)
		@echo "$(CYAN)The MINISHELL is ready :)$(EOC)"

clean :
		@/bin/rm -rf $(OBJ)
		@echo "$(GREEN)Clean MINISHELL$(EOC)"

fclean : clean
		@make -C ./libft fclean
		@/bin/rm -rf $(NAME)
		@/bin/rm -rf $(EXEC)
		@echo "$(GREEN)Total Clean MINISHELL$(EOC)"

re : fclean all

.PHONY : all fclean clean re
