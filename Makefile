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
	builtins_1.c \
	utils.c \
	utils_2.c \
	ft_echo.c \
	exec_cmds.c \
	prepare_redir.c \
	redirections.c

# Ajout des préfixes de dossiers
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# includes
LIBFT = $(LIBFT_DIR)/libft.a

# Cible principale
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ) $(LIBFT)
	@echo "🔨 Compiling libraries..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "✅ Libraries compiled successfully!"

# Compilation des fichiers objets dans OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "🔧 Compilation de $<..."
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Création du dossier OBJ_DIR si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "📦 Compiling lifbt..."
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
