/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 22:00:35 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define FOV 70
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# ifndef TILE_SIZE
#  define TILE_SIZE 10
# endif
# ifndef HEIGHT
#  define HEIGHT 480
# endif
# ifndef WIDTH
#  define WIDTH 640
# endif
# ifndef KEY_LEFT
#  define KEY_LEFT 100
# endif
# ifndef KEY_RIGHT
#  define KEY_RIGHT 97
# endif
# ifndef KEY_UP
#  define KEY_UP 119
# endif
# ifndef KEY_DOWN
#  define KEY_DOWN 115
# endif
# ifndef KEY_EXIT
#  define KEY_EXIT 65307
# endif
# ifndef KEY__ROT_LEFT
#  define KEY_ROT_LEFT 65361
# endif
# ifndef KEY_ROT_RIGHT
#  define KEY_ROT_RIGHT 65363
# endif

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define BOLD "\033[1m"
# define ERR_TEXTURE "Error : Map textures must have .xpm file extension\n"
# define ERR_COLORS "Error : Colors must have 3 values ranging from 0 to 255.\n"
# define ERR_LAST_ELEMENT "Error : The map must be the last element of the file\n"
# define ERR_WALL_MISSING "Error : The map is not enclosed by walls\n"
# define ERR_MAP_ELEMENTS "Error : Invalid map elements\n"
# define ERR_DUPLICATE_TEXTURE "Error : Duplicate textures\n"
# define ERR_TEXTURE_MISSING "Error: A texture is missing\n"
# define ERR_EAST_TEXTURE "Error: Failed to load east wall texture\n"
# define ERR_NORTH_TEXTURE "Error: Failed to load north wall texture\n"
# define ERR_WEST_TEXTURE "Error: Failed to load west wall texture\n"
# define ERR_SOUTH_TEXTURE "Error: Failed to load south wall texture\n"
# define DEBUG 0

// MLXXXXXXXXXXXXXXXXX
typedef struct s_tex
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				height;
	int				width;

}					t_tex;

// MATHSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
typedef struct s_ray
{
	double			fov;
	double			angle_ray;
	double			impact_x;
	double			impact_y;
	int				lineHauteur;
	int				drawStart;
	int				drawEnd;
	int				side;
	t_tex			*texture;
	double			dir_x;
	double			dir_y;
	int				flip_x;

}					t_ray;

typedef struct s_dda
{
	int				map_x;
	int				map_y;
	int				hit;
	int				step_x;
	int				step_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
}					t_dda;

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

// Mother Struct
typedef struct s_map
{
	// MLX
	void			*mlx;
	void			*win;

	int				current;
	t_tex			mur;
	t_tex			sol;
	t_tex			mur_NO;
	t_tex			mur_SO;
	t_tex			mur_WE;
	t_tex			mur_EA;

	// Keyboard
	int				flag_w;
	int				flag_s;
	int				flag_a;
	int				flag_d;
	int				flag_exit;
	int				flag_right;
	int				flag_left;
	float			move_speed;
	float			rot_speed;

	// Maths
	float			new_pos_y;
	float			new_pos_x;
	int				x;
	int				y;

	// Map
	int				mapx;
	int				mapy;
	double			dir_x;
	double			dir_y;
	float			angle;
	float			cx;
	float			cy;
	int				*play;
	t_dda			*dda;
	t_tex			*tex;
	t_ray			*ray;
	t_tex			buffer[2];
	t_data			*data;
}					t_map;
#endif

// MATHSSSSSSSSSSSSSSSSSS😭
void				draw_player(t_map *map);
void				draw_map(t_map *map);
void				draw_line(t_map *map, int x0, int y0, int x1, int y1,
						int color);
void				get_dda(t_map *map, t_ray *ray);
void				ft_draw_all_ray(t_map *map, t_ray *ray);
void				init_dda(t_map *map, double angle_ray);

// Graphisme
int					get_pixel_from_texture_safe(t_tex *tex, int x, int y);
void				my_pixel_put(t_tex *img, int x, int y, int color);
int				init_texture(t_map *map, t_data *data);
void				draw_background(t_map *map);
void				init_map(t_map *map, t_data *data);
t_tex				*choose_texture(t_map *map, t_ray *ray);
int					render_frame(t_map *map);
void				draw_texture_one(t_map *map, int x);

// Mouvement
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);

// Mouvement_utils

void				move_forward(t_map *map);
void				move_backward(t_map *map);
void				move_left(t_map *map);
void				move_right(t_map *map);
void				rotate_player(t_map *map);

// Free

void				free_map(char **map);
void				free_parsing(t_data *data);
void				destroy_images(t_map *map);
void				exit_safe(t_map *map);

// ===== srcs/parsing/ =====

// parsing.c

int					parsing(t_data *data);
void				parse_player(t_map *map, t_data *data);

// check_borders.c

int					check_borders(t_data *data);

// check_map_elements.c

int					check_map_elements(t_data *data);
int					verify_last_map_element(t_data *data, int i);

// set_colors.c

int					set_colors(t_data *data, char *line);

// set_map.c

char				**read_map(char *file);
char				**clean_map(char **map);
int					get_map_start_and_end(t_data *data);
void				set_map_highest_x(t_data *data);

// set_map2.c

char				**make_map_rectangular(t_data *data);

// set_textures.c

int					set_wall_textures(t_data *data, char *line);

// utils.c

void				t(int a);
int					validate_args(int ac, char **av);
int					first_char_index(char *line, int i);
int					find_last_map_element(char *line);

// verify_textures_and_colors.c

int					verify_texture_paths(t_data *data);
int					verify_colors(t_data *data);