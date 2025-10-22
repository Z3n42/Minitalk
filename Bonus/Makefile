# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 20:12:25 by ingonzal          #+#    #+#              #
#    Updated: 2021/08/24 21:01:43 by ingonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFLAGS += -s

SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -f

SANITIZE = -fsanitize=address -g3

LIBFT = -Llibft -lft

FILES_1 = server \

FILES_2 = client \
 
SRCS_DIR = ./
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS_1 = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_1)))
OBJS_2 = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_2)))

all: pre $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_1)
		$(CC) $(FLAGS) $^ $(LIBFT) -o $@ 

$(CLIENT): $(OBJS_2)
		$(CC) $(FLAGS) $^ $(LIBFT) -o $@ 
pre:
	$(MAKE) -C ./libft

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJS_1)
		$(RM) $(OBJS_2)

fclean: clean
		$(RM) $(SERVER)
		$(RM) $(CLIENT)
		$(MAKE) fclean -C ./libft

re: clean all

.PHONY: clean fclean %.o
