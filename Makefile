NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -O0
DEBUGFLAGS  = -Wall -Wextra -Werror -g3 -O0 -fsanitize=address -fsanitize=undefined -fsanitize=leak

RM          = rm -f
AR          = ar rcs

# --- Libs ---
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = ./minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

LDFLAGS     = -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

# --- Includes ---
INC_DIR     = ./include
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# --- Sources (liste manuelle) ---
SRC = \
	./srcs/main.c \
	./srcs/free.c \
	./srcs/maths/maths_map_un.c \
	./srcs/maths/maths_map_deux.c \
	./srcs/maths/maths_map_trois.c \
	./srcs/mouvement/mouvement.c \
	./srcs/mouvement/mouvement_utils.c \
	./srcs/graphisme/graphisme_un.c \
	./srcs/graphisme/graphisme_deux.c \
	./srcs/parsing/parsing.c \
	./srcs/parsing/check_borders.c \
	./srcs/parsing/check_map_elements.c \
	./srcs/parsing/set_colors.c \
	./srcs/parsing/set_map.c \
	./srcs/parsing/set_map2.c \
	./srcs/parsing/set_textures.c \
	./srcs/parsing/utils.c \
	./srcs/parsing/verify_textures_and_colors.c \


OBJ = $(SRC:.c=.o)

# --- Colors ---
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RED     = \033[0;31m
CYAN    = \033[0;36m
NC      = \033[0m

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)🔨 Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@echo "$(CYAN)⚙️  Compiling $(NC)$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Suppression des fichiers objets...$(NC)"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)💣 Suppression de l'exécutable...$(NC)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(YELLOW)🔍 Building $(NAME) with debug flags$(NC)"
	@$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
