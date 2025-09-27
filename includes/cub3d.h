/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/14 19:49:03 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define ERR_TEXTURE "Error : Map textures must have .xpm file extension\n"
#define ERR_COLORS "Error : Colors must have 3 values ranging from 0 to 255.\n"
#define ERR_LAST_ELEMENT "Error : The map must be the last element of the file\n"
#define ERR_WALL_MISSING "Error : The map is not enclosed by walls\n"
#define ERR_MAP_ELEMENTS "Error : Invalid map elements\n"
#define ERR_DUPLICATE_TEXTURE "Error : Duplicate textures\n"
#define ERR_TEXTURE_MISSING "Error: A texture is missing\n"
#define DEBUG 1

typedef struct s_data
{
	char			**map;
	char			*north_wall;
	char			*east_wall;
	char			*south_wall;
	char			*west_wall;
	int				*floor_color;
	int				*ceiling_color;
	unsigned long	floor_hex;
	unsigned long	ceiling_hex;
	int				map_start;
	int				map_end;
	int				map_height;
	int				map_highest_x;
}					t_data;

// ===== srcs/parsing/ =====

// check_borders.c

int					check_borders(t_data *data);
int					check_top_wall(t_data *data);
int					check_bottom_wall(t_data *data);
int					check_left_wall(t_data *data);
int					check_right_wall(t_data *data);

// check_map_elements.c

int					check_map_elements(t_data *data);
int					verify_last_map_element(t_data *data, int i);

// set_colors.c

int					set_floor_color(t_data *data, char *line);
int					set_ceiling_color(t_data *data, char *line);
int					set_colors(t_data *data, char *line);
int					is_polluted(char *line);

// set_map.c

char				**read_map(char *file);
char				**clean_map(char **map);
int					get_map_start_and_end(t_data *data);
void				set_map_highest_x(t_data *data);
char				**make_map_rectangular(t_data *data);

// set_map2.c

char				**make_map_rectangular(t_data *data);

// set_textures.c

char				*get_texture_path(char *line);
int					set_wall_textures(t_data *data, char *line);

// utils.c

void				t(int a);
int					validate_args(int ac, char **av);
int					first_char_index(char *line, int i);
int					find_last_map_element(char *line);

// verify_textures_and_colors.c

int					verify_texture_paths(t_data *data);
int					verify_colors(t_data *data);