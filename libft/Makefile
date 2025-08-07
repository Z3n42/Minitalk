# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/29 10:44:46 by ingonzal          #+#    #+#              #
#    Updated: 2021/08/24 20:22:24 by ingonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_memset \
		ft_strrchr \
		ft_printf/ft_printf \
		ft_printf/ft_putchar_pfd \
		ft_printf/ft_putnbr_pfd \
		ft_printf/ft_putnbr_hex \
		ft_printf/ft_putnbr_hexmay \
		ft_printf/ft_putnbr_long \
		ft_printf/ft_putnbr_p \
		ft_printf/ft_putstr_pfd \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_strlen \
		ft_putnbr_fd \
		ft_strlcpy \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_strlcpy \
		ft_strlcat \
		ft_bzero \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_itoa \
		ft_strmapi \
		ft_split \
		
FILES_B = ft_lstnew \
		  ft_lstadd_front \
	   	  ft_lstsize \
		  ft_lstlast \
	      ft_lstadd_back \
		  ft_lstdelone \
		  ft_lstclear \
		  ft_lstiter \
		  ft_lstmap \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(OBJS_B)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: clean fclean %.o
