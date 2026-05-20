NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(HEADERS)
LDFLAGS     = -Llibft -lft -lreadline
OBJ_DIR     = obj
HEADERS     = headers
SRC         = main.c signals.c io-redir.c \
              execution.c export.c export2.c env-exit.c \
              error-handle.c executeone.c execute-multiple.c \
              heredoc.c unset-echo-pwd.c cd.c \
              e_utils.c e_utils2.c env-utils3.c \
              expansion_utils.c lexer_utils.c \
              list_utils.c syntax_error.c syntax_error2.c \
              tokenization.c \
              parsing.c parsing_args.c parsing_cmd.c parsing_redir.c \
              expansion.c expansion2.c inserting.c execute_utils.c

OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT       = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C libft

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re