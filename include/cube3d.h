/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/28 05:08:40 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define FOV 150
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
	int		side;
	t_tex	*texture;
	double	dir_x;
	double	dir_y;
	int		flip_x;

}			t_ray;
typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		hit;
	int		step_x;
	int		step_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}			t_dda;
typedef struct s_draw
{
	int		y;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	double	dist;
	double	dist_corrected;
}			t_draw;
// Mother Struct
typedef struct s_map
{
	// MLX
	void	*mlx;
	void	*win;

	int		current;
	t_tex	mur;
	t_tex	sol;
	t_tex	mur_NO;
	t_tex	mur_SO;
	t_tex	mur_WE;
	t_tex	mur_EA;

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
	int		is_impact_x;
	int		is_impact_y;
	t_dda	*dda;
	t_tex	*tex;
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
void		get_dda(t_map *map, t_ray *ray);
void		ft_draw_all_ray(t_map *map, t_ray *ray);
void		draw_colonne(t_map *map, t_ray *ray, int x);
void		check_value(t_map *map, double wall_x, int x);
void		init_dda(t_map *map, double angle_ray);
void		get_dda_one(t_map *map);
void		get_dda_two(t_map *map, t_ray *ray);
void		get_dda_three(t_map *map, t_ray *ray);

// Graphisme
void		my_pixel_put(t_tex *img, int x, int y, int color);
void		init_texture(t_map *map);
void		clear_image(t_map *map, int color);
void		init_map(t_map *map);
int			render_frame(t_map *map);
void		draw_background(t_map *map);
t_tex		*choose_texture(t_map *map, t_ray *ray);
void		draw_texture_two(t_map *map, int col, int tex_x);
void		draw_texture_one(t_map *map, int x);
int			get_pixel_from_texture_safe(t_tex *tex, int x, int y);

// Mouvement
void		ft_moove(t_map *map);
void		init_flag(t_map *map);
int			refresh(void *param);
int			key_press(int keycode, void *param);
int			key_release(int keycode, void *param);
