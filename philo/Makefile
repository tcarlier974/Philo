NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread

SRCS = main.c \
	utils.c \
	parser.c \
	controle.c \
	init.c \
	dinner.c \
	mutex.c \
	sync.c \
	write.c \
	monitoring.c \

OBJS = $(SRCS:.c=.o)

.o : .c
	$(CC) $(CFLAGS) -c -o $@ $<.o : .c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re