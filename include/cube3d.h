/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/17 03:40:44 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define MAPX 10
# define MAPY 10

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# ifndef TILE_SIZE
#  define TILE_SIZE 100
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# ifndef WIDTH
#  define WIDTH 400
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

typedef struct s_map
{
	void	*mlx;
	void	*win;
	t_tex	buffer;
	t_tex	mur;
	t_tex	sol;

	int		flag_w;
	int		flag_s;
	int		flag_a;
	int		flag_d;
	int		flag_exit;
	int		flag_right;
	int		flag_left;
	int		img_height;
	int		img_width;
	float	pos_y;
	float	pos_x;
	float	new_pos_y;
	float	new_pos_x;

	int		x;
	int		y;
	void	*player;
	void	*droite;
	int		flag_col;
	int		mapx;
	int		mapy;
	double	dir_x;
	double	dir_y;
	float	angle;
	float	cx;
	float	cy;
	int		r;
	float	move_speed;
	float	rot_speed;
	int		play[MAPY][MAPX];

}			t_map;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dy;
	float	dx;
	t_map	*map;
}			t_ray;
#endif
