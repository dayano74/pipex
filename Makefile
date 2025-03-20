CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
LIBFTDIR := libft/

SRCS := main.c \
		execute_cmd.c \
		pipex.c \
		pipex_utils.c \



OBJS := $(SRCS:.c=.o)

LDFLAGS := -L./libft -lft

NAME := pipex

all : $(NAME)

$(NAME): $(OBJS)
		@make -C $(LIBFTDIR)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		$(RM) $(OBJS)
		@make -C $(LIBFTDIR) clean

fclean : clean
		$(RM) $(OBJS) $(NAME)
		@make -C $(LIBFTDIR) fclean

re : fclean all

.PHONY : all clean fclean re
