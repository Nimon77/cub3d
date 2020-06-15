# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 17:07:11 by nsimon            #+#    #+#              #
#    Updated: 2020/06/13 20:20:02 by nsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INC_PATH = ./includes/

SRC_PATH = ./srcs/

SRC_NAME =	main.c \
			check_map.c \
			error_check.c \
			events.c \
			get.c \
			init.c \
			move.c \
			parser.c \
			raycast.c \
			save.c \
			sprite.c \
			verif.c \
			wall_textures.c

UNAME_S := $(shell uname -s)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH = ./objs/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

LBPATH = ./libft/

LDFLAGS = -L$(LBPATH)

LDNAME = $(LBPATH)libftprintf.a

LDINCL = -I$(LBPATH)includes

MLXPATH = ./mlx/

ifeq ($(UNAME_S),Darwin)
	MLXINCL = -I$(MLXPATH)/osx/
	MLXNAME = $(MLXPATH)osx/libmlx.dylib
	MLXOPTION = -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME_S),Linux)
	MLXINCL = -I$(MLXPATH)/linux/
	MLXNAME = $(MLXPATH)linux/libmlx.a
	MLXOPTION = -lX11 -lm -lXext
endif

CC = gcc $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror

TEMP = .temp.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LBPATH)
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(OBJ) $(LDNAME) $(MLXNAME) $(MLXOPTION) -o$(NAME)
	@echo "\033[32m$(NAME) created\n\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I$(INC_PATH) $(LDINCL) $(MLXINCL) -o $@ -c $<

clean:
	@make clean -C $(LBPATH)
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@make fclean -C $(LBPATH)
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME) $(TEMP)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all

git:
	@git add .
	@git commit -m "$(NAME)"
	@git push

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h

.PHONY: all, clean, fclean, re
