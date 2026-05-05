NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -I$(HEADERS)
LDFLAGS     = -L$(SRC_DIR)/libft -lft -lreadline
SRC_DIR     = src
OBJ_DIR     = obj
HEADERS     = headers

# Execution sources (in src/execution/)
EXEC_FILES  = main.c signals.c utils.c utils2.c io-redir.c \
              execution.c env-utils.c built-ins.c built-ins2.c \
              error-handle.c executeone.c execute-multiple.c \
              heredoc.c

# Parsing sources (in src/parsing/)
PARSE_FILES = parsing-start.c error.c syntax_error.c

# Parsing subdirectory sources
PARSE_TOK   = tokenizer/tokenization.c tokenizer/lexer_utils.c \
              tokenizer/list_utils.c
PARSE_EXP   = expander/expansion.c expander/expansion_helpers.c \
              expander/inserting.c
PARSE_PAR   = parsing/parsing.c parsing/parsing_args.c \
              parsing/parsing_cmd.c parsing/parsing_redir.c

# Build full source paths
EXEC_SRC    = $(EXEC_FILES:%.c=$(SRC_DIR)/execution/%.c)
PARSE_SRC   = $(PARSE_FILES:%.c=$(SRC_DIR)/parsing/%.c) \
              $(PARSE_TOK:%.c=$(SRC_DIR)/parsing/%.c) \
              $(PARSE_EXP:%.c=$(SRC_DIR)/parsing/%.c) \
              $(PARSE_PAR:%.c=$(SRC_DIR)/parsing/%.c)

SRC         = $(EXEC_SRC) $(PARSE_SRC)

# Build object paths — flatten into obj/
EXEC_OBJ    = $(EXEC_FILES:%.c=$(OBJ_DIR)/exec_%.o)
PARSE_OBJ   = $(PARSE_FILES:%.c=$(OBJ_DIR)/parse_%.o)
PARSE_TOK_O = $(notdir $(PARSE_TOK:%.c=%.o))
PARSE_EXP_O = $(notdir $(PARSE_EXP:%.c=%.o))
PARSE_PAR_O = $(notdir $(PARSE_PAR:%.c=%.o))

OBJ         = $(EXEC_OBJ) $(PARSE_OBJ) \
              $(PARSE_TOK_O:%=$(OBJ_DIR)/parse_%) \
              $(PARSE_EXP_O:%=$(OBJ_DIR)/parse_%) \
              $(PARSE_PAR_O:%=$(OBJ_DIR)/parse_%)

LIBFT       = $(SRC_DIR)/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(SRC_DIR)/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- Execution pattern rule ---
$(OBJ_DIR)/exec_%.o: $(SRC_DIR)/execution/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Parsing top-level pattern rule ---
$(OBJ_DIR)/parse_%.o: $(SRC_DIR)/parsing/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Parsing/tokenizer pattern rule ---
$(OBJ_DIR)/parse_%.o: $(SRC_DIR)/parsing/tokenizer/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Parsing/expander pattern rule ---
$(OBJ_DIR)/parse_%.o: $(SRC_DIR)/parsing/expander/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Parsing/parsing pattern rule ---
$(OBJ_DIR)/parse_%.o: $(SRC_DIR)/parsing/parsing/%.c $(HEADERS)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(SRC_DIR)/libft clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	make -C $(SRC_DIR)/libft fclean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re