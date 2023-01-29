NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = sources
OBJS_DIR = objects
INCLUDES = -pthread
SRCS = $(addprefix $(SRCS_DIR)/,	main.c			\
									action.c		\
									init.c			\
									manage_forks.c	\
									monitoring.c	\
									check_args.c	\
									print_msg.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re