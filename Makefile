NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(HEADERS)
LDFLAGS     = -L$(SRC_DIR)/libft -lft -lreadline
SRC_DIR     = src
OBJ_DIR     = obj
HEADERS     = headers
FILES       = main.c signals.c utils.c utils2.c io-redir.c \
              execution.c env-utils.c built-ins.c built-ins2.c \
			  error-handle.c executeone.c test_parser.c execute-multiple.c \
			  heredoc.c
SRC         = $(FILES:%.c=$(SRC_DIR)/%.c)

OBJ         = $(FILES:%.c=$(OBJ_DIR)/%.o)

LIBFT       = $(SRC_DIR)/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(SRC_DIR)/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(SRC_DIR)/libft clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	make -C $(SRC_DIR)/libft fclean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re