# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 16:49:30 by msantos-          #+#    #+#              #
#    Updated: 2021/07/20 19:45:58 by msantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROGRAMS
PHILO = philo

INCLUDES = -I ./includes

#PATHS
OBJ_PATH = ./objs
SRC_PATH = ./srcs

#SRCS
SRCS = philo.c utils.c arg_validation.c
OBJS = $(SRCS:.c=.o)

#OBJS
OBJ = $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

#FLAGS
CC = gcc
CFLAGS = -Wall -Werror -Wextra

#INSTRUCTIONS
all:  philo

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(INCLUDES) -o $@ -c $^

philo: $(OBJ)
	$(CC) $(OBJ) -o $(PHILO)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(PHILO)
	@make fclean -C ft_printf_42 > /dev/null
	@make fclean -C libft_42 > /dev/null

re: fclean all
