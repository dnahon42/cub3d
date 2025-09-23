/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/23 22:39:46 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define MAPX 21
# define MAPY 21
# define FOV 60
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
#  define HEIGHT 640
# endif
# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef KEY_LEFT
#  define KEY_LEFT 97
# endif
# ifndef KEY_RIGHT
#  define KEY_RIGHT 100
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

// MLXXXXXXXXXXXXXXXXX
typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}			t_tex;

// MATHSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
typedef struct s_ray
{
	float	rx;
	float	ry;
	double	fov;
	double	angle_ray;
	double	impact_x;
	double	impact_y;
	float	dist;
	int		lineHauteur;
	float	fisheye;
	int		drawStart;
	int		drawEnd;

}			t_ray;

// Mother Struct
typedef struct s_map
{
	// MLX
	void	*mlx;
	void	*win;

	int		current;
	t_tex	mur;
	t_tex	sol;

	// Keyboard
	int		flag_w;
	int		flag_s;
	int		flag_a;
	int		flag_d;
	int		flag_exit;
	int		flag_right;
	int		flag_left;
	float	move_speed;
	float	rot_speed;

	// Maths
	int		img_height;
	int		img_width;
	float	pos_y;
	float	pos_x;
	float	new_pos_y;
	float	new_pos_x;
	int		x;
	int		y;

	// Map
	int		mapx;
	int		mapy;
	double	dir_x;
	double	dir_y;
	float	angle;
	float	cx;
	float	cy;
	int		*play;
	t_ray	*ray;
	t_tex	buffer[2];
}			t_map;
#endif

// MATHSSSSSSSSSSSSSSSSSS😭
void		draw_vector(t_map *map);
void		draw_player(t_map *map);
void		draw_square(t_map *map, int x, int y, int color);
void		draw_map(t_map *map);
void		draw_line(t_map *map, int x0, int y0, int x1, int y1, int color);
void		get_angle(t_map *map, t_ray *ray, double angle_ray);
void		ft_draw_all_ray(t_map *map, t_ray *ray);
void		draw_colonne(t_map *map, t_ray *ray, int x);

// Graphisme
void		my_pixel_put(t_tex *img, int x, int y, int color);
void		init_texture(t_map *map);
void		clear_image(t_map *map, int color);
void		init_map(t_map *map);
int			render_frame(t_map *map);
void		draw_background(t_map *map);

// Mouvement
void		ft_moove(t_map *map);
void		init_flag(t_map *map);
int			refresh(void *param);
int			key_press(int keycode, void *param);
int			key_release(int keycode, void *param);
