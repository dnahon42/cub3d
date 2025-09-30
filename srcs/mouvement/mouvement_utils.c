/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:31:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/09/27 18:32:24 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_map *map)
{
	int	next_x;
	int	next_y;
	int	index;

	next_x = (int)((map->cx + map->dir_x * map->move_speed) / TILE_SIZE);
	next_y = (int)((map->cy + map->dir_y * map->move_speed) / TILE_SIZE);
	index = next_y * map->mapx + next_x;
	if (map->play[index] == 1)
		return ;
	map->new_pos_x += map->dir_x * map->move_speed;
	map->new_pos_y += map->dir_y * map->move_speed;
}

void	move_backward(t_map *map)
{
	int	next_x;
	int	next_y;
	int	index;

	next_x = (int)((map->cx - map->dir_x * map->move_speed) / TILE_SIZE);
	next_y = (int)((map->cy - map->dir_y * map->move_speed) / TILE_SIZE);
	index = next_y * map->mapx + next_x;
	if (map->play[index] == 1)
		return ;
	map->new_pos_x -= map->dir_x * map->move_speed;
	map->new_pos_y -= map->dir_y * map->move_speed;
}

void	move_left(t_map *map)
{
	int	next_x;
	int	next_y;
	int	index;

	next_x = (int)((map->cx - map->dir_y * map->move_speed) / TILE_SIZE);
	next_y = (int)((map->cy + map->dir_x * map->move_speed) / TILE_SIZE);
	index = next_y * map->mapx + next_x;
	if (map->play[index] == 1)
		return ;
	map->new_pos_x -= map->dir_y * map->move_speed;
	map->new_pos_y += map->dir_x * map->move_speed;
}

void	move_right(t_map *map)
{
	int	next_x;
	int	next_y;
	int	index;

	next_x = (int)((map->cx + map->dir_y * map->move_speed) / TILE_SIZE);
	next_y = (int)((map->cy - map->dir_x * map->move_speed) / TILE_SIZE);
	index = next_y * map->mapx + next_x;
	if (map->play[index] == 1)
		return ;
	map->new_pos_x += map->dir_y * map->move_speed;
	map->new_pos_y -= map->dir_x * map->move_speed;
}

void	rotate_player(t_map *map)
{
	if (map->flag_left)
		map->angle -= map->rot_speed;
	if (map->flag_right)
		map->angle += map->rot_speed;
	map->dir_x = cos(map->angle);
	map->dir_y = sin(map->angle);
	if (map->angle < 0)
		map->angle += 2 * M_PI;
	if (map->angle >= 2 * M_PI)
		map->angle -= 2 * M_PI;
}
