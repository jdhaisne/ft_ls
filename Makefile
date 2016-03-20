# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/18 16:15:23 by jdhaisne          #+#    #+#              #
#    Updated: 2016/03/19 15:56:18 by jdhaisne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = check.c \
	  get_data1.c \
	  get_data2.c \
	  get_data3.c \
	  list.c \
	  main.c \
	  read.c \
	  read2.c

OBJ = check.o \
	  get_data1.o \
	  get_data2.o \
	  get_data3.o \
	  list.o \
	  main.o \
	  read.o \
	  read2.o

LIB = libft.a

CFLAG = -Wall -Werror -Wextra

LIBFT_DIR = libft

all : $(NAME)

$(NAME) :
	make -C $(LIBFT_DIR) re
	gcc -c $(SRC) $(CFLAG)
	gcc -o $(NAME) $(OBJ) $(LIBFT_DIR)/$(LIB)

.PHONY:clean
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
