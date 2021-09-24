# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 16:49:30 by msantos-          #+#    #+#              #
#    Updated: 2021/09/24 21:46:43 by msantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROGRAMS
PHILO = philo

INCLUDES = -I ./includes

#PATHS
OBJ_PATH = ./objs
SRC_PATH = ./srcs

#SRCS
SRCS = philo.c utils.c utils2.c arg_validation.c philo_actions.c time.c deathrelated.c
OBJS = $(SRCS:.c=.o)

#OBJS
OBJ = $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

#FLAGS
CC = gcc
CFLAGS = -Wall -Werror -Wextra
THREADFLAG = -pthread

#INSTRUCTIONS
all:  philo

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -g $(CFLAGS)  $(INCLUDES) -o $@  -c $^

philo: $(OBJ)
	$(CC)   $(OBJ) -o $(PHILO)
normi:
	norminette srcs/*.c

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(PHILO) 

re: fclean all
