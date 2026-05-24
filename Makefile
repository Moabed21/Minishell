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

# ── Colors ────────────────────────────────────────────────────────────────────
RESET       = \033[0m
DIM         = \033[2m
CYAN        = \033[36m
BCYAN       = \033[1;36m
BGREEN      = \033[1;32m
YELLOW      = \033[1;33m
BRED        = \033[1;31m
WHITE       = \033[1;97m

# ── Progress bar helper ───────────────────────────────────────────────────────
TOTAL       := $(words $(SRC))
CURRENT     := 0

define progress
	$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1)))) \
	$(eval PCT     := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL))))) \
	$(eval FILLED  := $(shell echo $$(($(CURRENT) * 30  / $(TOTAL))))) \
	$(eval EMPTY   := $(shell echo $$((30 - $(FILLED))))) \
	@printf "\033[2K\r  $(BRED)[$(BCYAN)"; \
	printf '%0.s█' $$(seq 1 $(FILLED)); \
	printf "$(DIM)$(WHITE)"; \
	printf '%0.s░' $$(seq 1 $(EMPTY)); \
	printf "$(BRED)] $(RESET)$(YELLOW)%3d%%$(RESET)  $(DIM)$(WHITE)%-28s$(RESET)" \
		"$(PCT)" "$(1)";
endef

# ── Rules ─────────────────────────────────────────────────────────────────────
all: $(LIBFT) _header $(OBJ)
	@printf "\n\n"
	@printf "  $(BRED)╔══════════════════════════════════════╗$(RESET)\n"
	@printf "  $(BRED)║ $(YELLOW)%-36s$(BRED)║$(RESET)\n" "  Linking  →  $(NAME)"
	@printf "  $(BRED)╚══════════════════════════════════════╝$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@printf "\n  $(BGREEN)✓  Build complete!$(RESET)  $(DIM)→  ./$(NAME)$(RESET)\n\n"

_header:
	@printf "\n  $(BCYAN)Minishell$(RESET) $(DIM)│$(RESET) $(YELLOW)%d files to compile$(RESET)\n\n" $(TOTAL)

$(LIBFT):
	@printf "  $(BRED)► Building libft...$(RESET) "
	@$(MAKE) -s --no-print-directory -C libft
	@printf "$(BGREEN)✓$(RESET)\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(call progress,$<)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@printf "  $(BRED)► Cleaning...$(RESET) "
	@$(MAKE) -s --no-print-directory -C libft clean
	@rm -rf $(OBJ_DIR)
	@printf "$(BGREEN)✓$(RESET)\n"

fclean: clean
	@printf "  $(BRED)► Removing $(NAME)...$(RESET) "
	@$(MAKE) -s --no-print-directory -C libft fclean
	@rm -f $(NAME)
	@printf "$(BGREEN)✓$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re _header