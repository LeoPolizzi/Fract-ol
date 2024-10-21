# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 20:18:29 by lpolizzi          #+#    #+#              #
#    Updated: 2024/10/14 16:55:30 by lpolizzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMP = cc
CFLAGS = -Wall -Wextra -Werror -I ./
NAME = libft.a

ADDI =  ft_strjoin.c			ft_substr.c					ft_strtrim.c			ft_split.c			\
	    ft_itoa.c				ft_strmapi.c				ft_striteri.c			ft_putchar_fd.c		\
	    ft_putstr_fd.c			ft_putendl_fd.c				ft_putnbr_fd.c

LIBC =  ft_atoi.c				ft_bzero.c					ft_isalnum.c			ft_isalpha.c		\
	    ft_isascii.c			ft_isdigit.c				ft_isprint.c			ft_memchr.c			\
	    ft_memcmp.c				ft_memcpy.c					ft_memmove.c			ft_memset.c			\
	    ft_strchr.c				ft_strdup.c					ft_strlcat.c			ft_strlcpy.c		\
	    ft_strlen.c				ft_strncmp.c				ft_strnstr.c			ft_strrchr.c		\
	    ft_tolower.c			ft_toupper.c				ft_calloc.c

BONUS = ft_lstnew_bonus.c		ft_lstadd_front_bonus.c		ft_lstsize_bonus.c		ft_lstlast_bonus.c	\
		ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c		ft_lstclear_bonus.c		ft_lstiter_bonus.c	\
		ft_lstmap_bonus.c

SRCS = ${LIBC} ${ADDI}
SRCS_BONUS = ${SRCS} ${BONUS}

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
						ar rcs ${NAME} ${OBJS}

bonus: ${OBJS_BONUS}
						ar rcs ${NAME} ${OBJS_BONUS}

.c.o:
						${COMP} ${CFLAGS} -c $< -o $@

clean:
						rm -rf ${OBJS} ${OBJS_BONUS}

fclean: clean
						rm -rf ${NAME}

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re rebonus
