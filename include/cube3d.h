/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:51:38 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/13 22:41:33 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_map
{
	int		flag_w;
	int		flag_s;
	int		flag_a;
	int		flag_d;
	int		flag_exit;
	float	pos_y;
	float	pos_x;
	float	new_pos_y;
	float	new_pos_x;
	int		x;
	int		y;
	void	*mlx;
	void	*win;
	void	*player;
	void	*mur;
	void	*sol;
	void	*droite;
	int		flag_col;
	int		img_width;
	int		img_height;
	int		mapx;
	int		mapy;
	int		dir_x;
	int		dir_y;
}			t_map;
#endif
