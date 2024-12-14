# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efaustin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 16:10:29 by efaustin          #+#    #+#              #
#    Updated: 2024/12/10 16:11:14 by efaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRCS	=   src/main.c \
			src/fts_aux.c \
			src/fts_init.c \
			src/fts_dead.c \
			src/fts_state.c \
			src/fts_philo.c \
			src/fts_forks.c \
			src/fts_check.c \
			src/fts_utils.c \
			src/fts_thread.c \
            src/fts_program.c

OBJS	= $(SRCS:.c=.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
