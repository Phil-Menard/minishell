CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g
NAME = minishell

# Dossiers
SRC_DIR = srcs
OBJ_DIR = objs
LIBFT_DIR = libft

# Fichiers sources
SRC = minishell.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	execution/execve.c \
	execution/exec_cmds.c \
	execution/exec_cmds_utils.c \
	execution/pipex.c \
	execution/utils_pipex.c \
	utils/utils.c \
	utils/utils_2.c \
	utils/utils_3.c \
	utils/utils_fd.c \
	utils/utils_fd_2.c \
	utils/utils_export.c \
	utils/utils_free.c \
	redirections/redirections.c \
	env/init_env.c \
	env/utils_env.c \
	signals/signals.c \
	parsing2/tokenizer.c \
	parsing2/parser.c \
	parsing2/set_cmd_line.c \
	parsing2/utils_parsing.c \
	parsing2/heredoc_utils.c \

# Ajout des préfixes de dossiers
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# includes
LIBFT = $(LIBFT_DIR)/libft.a

# Cible principale
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ) $(LIBFT)
	@echo "🔨 Compiling..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "✅ Compiled successfully!"

# Compilation des fichiers objets dans OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "🔧 Compiling $<..."
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Création du dossier OBJ_DIR si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "📦 Adding lifbt..."
	@make -s -C $(LIBFT_DIR)

# Nettoyage des fichiers objets et du dossier OBJ_DIR
clean:
	@echo "🧹 Cleaning .o of $(NAME), $(LIBFT)..."
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean

# Nettoyage complet
fclean: clean
	@echo "🗑️ Deleting $(NAME), $(LIBFT), ..."
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

# Rebuild complet
re: fclean all
