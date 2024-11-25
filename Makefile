NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRC		=	src/main.c \
			src/init.c \
			src/check.c \
			src/routine.c \
			src/monitor.c \
			src/utils.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
