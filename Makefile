# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelouch <obelouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 14:29:38 by obelouch          #+#    #+#              #
#    Updated: 2019/05/22 23:06:01 by obelouch         ###   ########.fr        #
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
			affect dollar cd env echo pwd exit setenv unsetenv printenv\
			init_fill_env rel_path show_env exec_cmd launcher signals\
			clean_quote ms_tools tools2 exec wildcard wildcard_manage\
			wildcard_tools usages dicstr expansions\

SRC = $(addprefix src/, $(addsuffix .c, $(MINISHELL)))

OBJ = $(addsuffix .o, $(MINISHELL))

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
		@make -C ./libft re && make -C ./libft clean
		@gcc -c $(FLAGS) -I ./ $(SRC)
		@gcc -o $(NAME) $(OBJ) $(LIB)
		@echo "\n"
		@echo "$(CYAN)   ██████╗ ██████╗ ███████╗██╗  ██╗"
		@echo "$(CYAN)  ██╔═══██╗██╔══██╗██╔════╝██║  ██║"
		@echo "$(CYAN)  ██║   ██║██████╔╝███████╗███████║"
		@echo "$(CYAN)  ██║   ██║██╔══██╗╚════██║██╔══██║"
		@echo "$(CYAN)  ╚██████╔╝██████╔╝███████║██║  ██║"
		@echo "$(CYAN)   ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝$(EOC)"
		@echo "$(GREEN)        V2.0$(EOC)    by:$(GREEN) obelouch\n$(EOC)"

clean :
		@/bin/rm -rf $(OBJ)
		@echo "$(GREEN)Clean MINISHELL$(EOC)"

fclean : clean
		@make -C ./libft fclean
		@/bin/rm -rf $(NAME)
		@echo "$(GREEN)Total Clean MINISHELL$(EOC)"

re : fclean all

