/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:25:19 by kiteixei          #+#    #+#             */
/*   Updated: 2025/09/27 21:40:18 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_moove(t_map *map)
{
	map->move_speed = 0.3 * TILE_SIZE;
	map->rot_speed = 0.25;
	map->new_pos_x = map->cx;
	map->new_pos_y = map->cy;
	if (map->flag_w)
		move_forward(map);
	if (map->flag_s)
		move_backward(map);
	if (map->flag_a)
		move_left(map);
	if (map->flag_d)
		move_right(map);
	rotate_player(map);
	map->cx = map->new_pos_x;
	map->cy = map->new_pos_y;
}

static void	init_flag(t_map *map)
{
	map->flag_w = 0;
	map->flag_s = 0;
	map->flag_a = 0;
	map->flag_d = 0;
	map->flag_right = 0;
	map->flag_left = 0;
}

static int	refresh(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	ft_moove(map);
	init_flag(map);
	map->cx = map->new_pos_x;
	map->cy = map->new_pos_y;
	render_frame(map);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == KEY_UP)
		map->flag_w = 1;
	else if (keycode == KEY_DOWN)
		map->flag_s = 1;
	else if (keycode == KEY_LEFT)
		map->flag_a = 1;
	else if (keycode == KEY_RIGHT)
		map->flag_d = 1;
	else if (keycode == KEY_ROT_RIGHT)
		map->flag_right = 1;
	else if (keycode == KEY_ROT_LEFT)
		map->flag_left = 1;
	else if (keycode == KEY_EXIT)
		exit_safe(map);
	return (refresh(map));
}

int	key_release(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == KEY_LEFT)
		map->flag_a = 0;
	else if (keycode == KEY_RIGHT)
		map->flag_d = 0;
	else if (keycode == KEY_UP)
		map->flag_w = 0;
	else if (keycode == KEY_DOWN)
		map->flag_s = 0;
	else if (keycode == KEY_ROT_RIGHT)
		map->flag_right = 0;
	else if (keycode == KEY_ROT_LEFT)
		map->flag_left = 0;
	else if (keycode == KEY_EXIT)
		map->flag_exit = 0;
	return (refresh(map));
}
