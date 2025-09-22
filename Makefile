
NAME 		= 	cub3d
CC 			= 	cc
CFLAGS 		= 	-g3 -O0 -Wall -Wextra -Werror
DEBUGFLAGS	= 	-g3 -O0 -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak

LDFLAGS		= 	-lreadline -Llibft -lft
AR 			= 	ar rcs
RM 			= 	rm -f


MLX_DIR     = ./minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

LDFLAGS     = -Llibft -lft $(MLX_FLAGS)
SRC_DIR 	=   ./src
SRC 			=   main.c	
LIBFT 		= 	./libft/libft.a
INCLUDES	= 	./includes/cub3d.h ./libft/includes/libft.h

OBJ 		= 	$(SRC:.c=.o)
OBJ_B 		= 	$(SRC_B:.c=.o)

# Color codes
GREEN 		= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RED 		= 	\033[0;31m
BLUE 		= 	\033[0;34m
PURPLE 		= 	\033[0;35m
CYAN 		= 	\033[0;36m
NC 			= 	\033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)Building $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Suppression des fichiers objets...$(RESET)"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	@echo "$(RED)💣 Suppression de l'exécutable...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
re: fclean all

debug: $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@echo "$(YELLOW)Building $(NC)$(NAME) $(YELLOW)with debug flags"
	@$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Lancement de Valgrind sur ./minishell..."
	valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./main

.PHONY: all clean fclean re debug valgrind
