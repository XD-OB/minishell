# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 14:29:38 by obelouch          #+#    #+#              #
#    Updated: 2019/05/09 15:17:54 by obelouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
EOC = \033[1;0m

NAME = minishell

MINISHELL = main prompt tools cmdsplit cmd_user cd echo exit\

SRC = $(addprefix src/, $(addsuffix .c, $(MINISHELL)))

OBJ = $(addsuffix .o, $(MINISHELL))

FLAGS = 

all : $(NAME)

$(NAME) :
		@make -C ./libft re && make -C ./libft clean
		@gcc -c  $(FLAGS) -I ./ $(SRC)
		@gcc -o $(NAME) $(OBJ) -L ./libft -lft
		@echo "$(CYAN)The MINISHELL is ready :)$(EOC)"

clean :
		@/bin/rm -rf $(OBJ)
		@echo "$(GREEN)Clean MINISHELL$(EOC)"

fclean : clean
		@make -C ./libft fclean
		@/bin/rm -rf $(NAME)
		@echo "$(GREEN)Total Clean MINISHELL$(EOC)"

re : fclean all

.PHONY : all fclean clean re
