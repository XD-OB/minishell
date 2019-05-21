# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelouch <obelouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 14:29:38 by obelouch          #+#    #+#              #
#    Updated: 2019/05/21 06:29:46 by obelouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
EOC = \033[1;0m

NAME = minishell

LIB = -L ./libft -lft

MINISHELL = ft_split_quote ft_split_invquote main prompt tools cmdsplit\
			cd env echo pwd setenv unsetenv printenv dollarenv show_env usages\
			init_fill_env rel_path print_echo exec_cmd launcher signals\
			clean_quote ms_tools tools2 exec wildcard wildcard_manage\
			wildcard_tools\

SRC = $(addprefix src/, $(addsuffix .c, $(MINISHELL)))

OBJ = $(addsuffix .o, $(MINISHELL))

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
		@make -C ./libft re && make -C ./libft clean
		@gcc -c $(FLAGS) -I ./ $(SRC)
		@gcc -o $(NAME) $(OBJ) $(LIB)
		@echo "$(CYAN) _______ __     _______ __ "
		@echo "$(CYAN)|       |  |--.|     __|  |--."
		@echo "$(CYAN)|   -   |  _  ||__     |     |"
		@echo "$(CYAN)|_______|_____||_______|__|__|$(EOC)"
		@echo "$(GREEN)    V1.0.1$(EOC)   by:$(GREEN) obelouch\n$(EOC)"

clean :
		@/bin/rm -rf $(OBJ)
		@echo "$(GREEN)Clean MINISHELL$(EOC)"

fclean : clean
		@make -C ./libft fclean
		@/bin/rm -rf $(NAME)
		@echo "$(GREEN)Total Clean MINISHELL$(EOC)"

re : fclean all

.PHONY : all fclean clean re
