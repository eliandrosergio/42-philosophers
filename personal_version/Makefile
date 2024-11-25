ECHO	= @echo
RED     = \033[31m
MAGENTA	= \033[35m
YELLOW  = \033[33m
BLUE    = \033[34m
BOLD	= \033[1m
NORMAL	= \033[0m

NAME    = philo
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pthread

SRC     = src/main.c \
          src/init.c \
          src/check.c \
          src/routine.c \
          src/monitor.c \
          src/utils.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(ECHO) "$(BLUE)$(BOLD)[Compilando o programa...]$(NORMAL)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	$(ECHO) "$(MAGENTA)$(BOLD)[Compilação concluída com sucesso!]$(NORMAL)"

clean:
	$(ECHO) "$(YELLOW)$(BOLD)[Removendo arquivos objetos...]$(NORMAL)"
	@rm -f $(OBJ)
	$(ECHO) "$(MAGENTA)$(BOLD)[Arquivos objetos removidos!]$(NORMAL)"

fclean: clean
	$(ECHO) "$(RED)$(BOLD)[Removendo o executável...]$(NORMAL)"
	@rm -f $(NAME)
	$(ECHO) "$(MAGENTA)$(BOLD)[Executável removido!]$(NORMAL)"

re: fclean all

src/main.o: src/main.c
	@$(CC) $(CFLAGS) -c src/main.c -o src/main.o
src/init.o: src/init.c
	@$(CC) $(CFLAGS) -c src/init.c -o src/init.o
src/check.o: src/check.c
	@$(CC) $(CFLAGS) -c src/check.c -o src/check.o
src/routine.o: src/routine.c
	@$(CC) $(CFLAGS) -c src/routine.c -o src/routine.o
src/monitor.o: src/monitor.c
	@$(CC) $(CFLAGS) -c src/monitor.c -o src/monitor.o
src/utils.o: src/utils.c
	@$(CC) $(CFLAGS) -c src/utils.c -o src/utils.o

