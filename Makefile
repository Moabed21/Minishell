NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(HEADERS)
LDFLAGS     = -L$(SRC_DIR)/libft -lft -lreadline
SRC_DIR     = src
OBJ_DIR     = obj
HEADERS     = headers

EXEC_FILES  = main.c signals.c io-redir.c \
              execution.c built-ins.c built-ins2.c \
              error-handle.c executeone.c execute-multiple.c \
              heredoc.c built-ins3.c built-ins4.c

UTILS_FILES = e_utils.c e_utils2.c env-utils3.c \
              expansion_utils.c lexer_utils.c \
              list_utils.c syntax_error.c

TOK_FILES   = tokenization.c
PARSE_FILES = parsing.c parsing_args.c parsing_cmd.c parsing_redir.c
EXP_FILES   = expansion.c inserting.c

EXEC_SRC    = $(EXEC_FILES:%.c=$(SRC_DIR)/execution/%.c)
UTILS_SRC   = $(UTILS_FILES:%.c=$(SRC_DIR)/utils/%.c)
TOK_SRC     = $(TOK_FILES:%.c=$(SRC_DIR)/tokenizer/%.c)
PARSE_SRC   = $(PARSE_FILES:%.c=$(SRC_DIR)/parse/%.c)
EXP_SRC     = $(EXP_FILES:%.c=$(SRC_DIR)/expander/%.c)

SRC         = $(EXEC_SRC) $(UTILS_SRC) $(TOK_SRC) $(PARSE_SRC) $(EXP_SRC)

OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT       = $(SRC_DIR)/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(SRC_DIR)/libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/tokenizer
	@mkdir -p $(OBJ_DIR)/parse
	@mkdir -p $(OBJ_DIR)/expander

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(SRC_DIR)/libft clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(SRC_DIR)/libft fclean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
