##
## EPITECH PROJECT, 2018
## 
## File description:
## 
##

NAME	= strace

CC	= gcc

RM	= rm -f

SRCS	= ./src/die.c \
	  ./src/formatting.c \
	  ./src/main.c \
	  ./src/signals.c \
	  ./src/strace.c \
	  ./src/count.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -W -Wall -Wextra -O3 -pedantic

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re strace
