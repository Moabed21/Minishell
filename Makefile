NAME=minishell
CC=cc
CFLAGS= -Wall -Wextra -Werror -lreadline
SRC_DIR = src
SRC=$(SRC_DIR)/main.c $(SRC_DIR)/signals.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils2.c $(SRC_DIR)/io-redir.c \
	$(SRC_DIR)/execution.c $(SRC_DIR)/env-utils.c $(SRC_DIR)/built-ins.c $(SRC_DIR)/built-ins2.c
all:

clean:

fclean:

re: