CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
LIBFTDIR := libft/

SRCS_DIR := mand
SRCS_FILES :=	main.c \
				execute_cmd.c \
				pipex.c \
				pipex_utils.c
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
MAND_OBJS := $(SRCS:.c=.o)

BONUS_SRCS_DIR := bonus
BONUS_SRCS_FILES :=	main_bonus.c \
					pipex_bonus.c \
					build_tree_bonus.c \
					create_node_bonus.c \
					execute_cmd_bonus.c \
					pipex_utils_bonus.c \
					free_bonus.c \
					here_doc_bonus.c
BONUS_SRCS := $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_FILES))
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

PIPEX_OBJS := $(MAND_OBJS)

LDFLAGS := -L./libft -lft

NAME := pipex

BONUS_STAMP := .bonus_stamp

all: $(NAME)

$(NAME): $(PIPEX_OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(PIPEX_OBJS) -o $(NAME) $(LDFLAGS)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_SRCS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(BONUS_OBJS)
	$(MAKE) PIPEX_OBJS="$(BONUS_OBJS)" $(NAME)
	touch $(BONUS_STAMP)

clean:
	$(RM) $(MAND_OBJS) $(BONUS_OBJS) $(BONUS_STAMP)
	@make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
